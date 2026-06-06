namespace youklx {

Vulkan& Vulkan::updateFontTexture(Font* font) {
    if (!font || !font->loaded) return *this;
    if (font->numPages == 0 || font->atlasPages.empty()) return *this;
    if (!font->atlasDirty) return *this;  // 图集未变化，跳过重建

    font->atlasDirty = false;

    int tw = font->atlasW;
    int pageH = font->atlasH;
    int totalH = pageH * font->numPages;
    vk::DeviceSize rowSize = static_cast<vk::DeviceSize>(tw) * 4;
    vk::DeviceSize imgSize = rowSize * totalH;

    // 竖直堆叠所有页面到单张图集
    std::vector<uint8_t> stacked(totalH * tw * 4);
    for (int pg = 0; pg < font->numPages; ++pg) {
        const uint8_t* src = font->atlasPages[pg].data();
        uint8_t* dst = stacked.data() + (size_t)pg * pageH * tw * 4;
        memcpy(dst, src, pageH * tw * 4);
    }

    // 上传到 GPU
    vk::BufferCreateInfo stagingInfo{{}, imgSize, vk::BufferUsageFlagBits::eTransferSrc};
    auto stagingReqs = vk::raii::Buffer{*this->device, stagingInfo}.getMemoryRequirements();
    vk::raii::DeviceMemory stagingMem{*this->device,
        vk::MemoryAllocateInfo{stagingReqs.size,
            findMemoryType(stagingReqs.memoryTypeBits,
                vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent)}};
    vk::raii::Buffer stagingBuf{*this->device, stagingInfo};
    stagingBuf.bindMemory(*stagingMem, 0);
    void* ptr = stagingMem.mapMemory(0, imgSize);
    memcpy(ptr, stacked.data(), static_cast<size_t>(imgSize));
    stagingMem.unmapMemory();

    this->device->waitIdle();
    this->fontImage.reset();
    this->fontImageMemory.reset();
    this->fontImageView.reset();
    this->fontSampler.reset();

    vk::ImageCreateInfo imgInfo{{}, vk::ImageType::e2D, vk::Format::eR8G8B8A8Srgb,
        {static_cast<uint32_t>(tw), static_cast<uint32_t>(totalH), 1}, 1, 1,
        vk::SampleCountFlagBits::e1, vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled};
    this->fontImage.emplace(*this->device, imgInfo);
    auto memReqs = this->fontImage->getMemoryRequirements();
    this->fontImageMemory.emplace(*this->device,
        vk::MemoryAllocateInfo{memReqs.size, findMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)});
    this->fontImage->bindMemory(*this->fontImageMemory, 0);

    vk::raii::CommandBuffer copyCmd = std::move(
        this->device->allocateCommandBuffers(vk::CommandBufferAllocateInfo{*this->commandPool, vk::CommandBufferLevel::ePrimary, 1}).front());
    copyCmd.begin(vk::CommandBufferBeginInfo{vk::CommandBufferUsageFlagBits::eOneTimeSubmit});
    vk::ImageMemoryBarrier barrier{vk::AccessFlagBits::eNone, vk::AccessFlagBits::eTransferWrite,
        vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, *this->fontImage,
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}};
    copyCmd.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer, {}, nullptr, nullptr, barrier);
    vk::BufferImageCopy copyRegion{0, 0, 0, {vk::ImageAspectFlagBits::eColor, 0, 0, 1}, {0, 0, 0}, {static_cast<uint32_t>(tw), static_cast<uint32_t>(totalH), 1}};
    copyCmd.copyBufferToImage(*stagingBuf, *this->fontImage, vk::ImageLayout::eTransferDstOptimal, copyRegion);
    vk::ImageMemoryBarrier barrier2{vk::AccessFlagBits::eTransferWrite, vk::AccessFlagBits::eShaderRead,
        vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, *this->fontImage,
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}};
    copyCmd.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader, {}, nullptr, nullptr, barrier2);
    copyCmd.end();
    this->graphicsQueue->submit(vk::SubmitInfo{0, nullptr, nullptr, 1, &*copyCmd});
    this->graphicsQueue->waitIdle();

    this->fontImageView.emplace(*this->device,
        vk::ImageViewCreateInfo{{}, *this->fontImage, vk::ImageViewType::e2D, vk::Format::eR8G8B8A8Srgb,
            {}, {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}});
    this->fontSampler.emplace(*this->device,
        vk::SamplerCreateInfo{{}, vk::Filter::eLinear, vk::Filter::eLinear, vk::SamplerMipmapMode::eLinear,
            vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge, vk::SamplerAddressMode::eClampToEdge});

    {
        vk::DescriptorImageInfo imageInfo{*this->fontSampler, *this->fontImageView, vk::ImageLayout::eShaderReadOnlyOptimal};
        vk::WriteDescriptorSet writeDesc{**this->fontDescSet, 0, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo, nullptr, nullptr};
        this->device->updateDescriptorSets(writeDesc, nullptr);
    }

    return *this;
}

}