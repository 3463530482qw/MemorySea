namespace youklx {

Vulkan& Vulkan::updateTexture(Image& img) {
    // 纹理未变化时跳过重建（图片是静态数据，只需构建一次）
    if (textureBuilt) return *this;

    img.buildAtlas();  // 确保图集已构建

    if (img.atlasData.empty() || img.atlasW == 0 || img.atlasH == 0) return *this;

    int texW = img.atlasW, texH = img.atlasH;
    vk::DeviceSize imgSize = static_cast<vk::DeviceSize>(texW) * texH * 4;

    vk::BufferCreateInfo stagingInfo{{}, imgSize, vk::BufferUsageFlagBits::eTransferSrc};
    vk::raii::Buffer stagingBuf{*this->device, stagingInfo};
    auto stagingReqs = stagingBuf.getMemoryRequirements();
    vk::raii::DeviceMemory stagingMem{*this->device,
        vk::MemoryAllocateInfo{stagingReqs.size,
            findMemoryType(stagingReqs.memoryTypeBits,
                vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent)}};
    stagingBuf.bindMemory(*stagingMem, 0);
    void* ptr = stagingMem.mapMemory(0, imgSize);
    memcpy(ptr, img.atlasData.data(), static_cast<size_t>(imgSize));
    stagingMem.unmapMemory();

    this->device->waitIdle();
    this->dummyImage.reset();
    this->dummyImageMemory.reset();
    this->dummyImageView.reset();

    vk::ImageCreateInfo imgInfo{{}, vk::ImageType::e2D, vk::Format::eR8G8B8A8Srgb,
        {static_cast<uint32_t>(texW), static_cast<uint32_t>(texH), 1}, 1, 1,
        vk::SampleCountFlagBits::e1, vk::ImageTiling::eOptimal,
        vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled};
    this->dummyImage.emplace(*this->device, imgInfo);
    auto memReqs = this->dummyImage->getMemoryRequirements();
    this->dummyImageMemory.emplace(*this->device,
        vk::MemoryAllocateInfo{memReqs.size, findMemoryType(memReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)});
    this->dummyImage->bindMemory(*this->dummyImageMemory, 0);

    vk::raii::CommandBuffer copyCmd = std::move(
        this->device->allocateCommandBuffers(vk::CommandBufferAllocateInfo{*this->commandPool, vk::CommandBufferLevel::ePrimary, 1}).front());
    copyCmd.begin(vk::CommandBufferBeginInfo{vk::CommandBufferUsageFlagBits::eOneTimeSubmit});
    vk::ImageMemoryBarrier barrier{vk::AccessFlagBits::eNone, vk::AccessFlagBits::eTransferWrite,
        vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal,
        VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, *this->dummyImage,
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}};
    copyCmd.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer, {}, nullptr, nullptr, barrier);
    vk::BufferImageCopy copyRegion{0, 0, 0, {vk::ImageAspectFlagBits::eColor, 0, 0, 1}, {0, 0, 0}, {static_cast<uint32_t>(texW), static_cast<uint32_t>(texH), 1}};
    copyCmd.copyBufferToImage(*stagingBuf, *this->dummyImage, vk::ImageLayout::eTransferDstOptimal, copyRegion);
    vk::ImageMemoryBarrier barrier2{vk::AccessFlagBits::eTransferWrite, vk::AccessFlagBits::eShaderRead,
        vk::ImageLayout::eTransferDstOptimal, vk::ImageLayout::eShaderReadOnlyOptimal,
        VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, *this->dummyImage,
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}};
    copyCmd.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader, {}, nullptr, nullptr, barrier2);
    copyCmd.end();
    this->graphicsQueue->submit(vk::SubmitInfo{0, nullptr, nullptr, 1, &*copyCmd});
    this->graphicsQueue->waitIdle();

    this->dummyImageView.emplace(*this->device,
        vk::ImageViewCreateInfo{{}, *this->dummyImage, vk::ImageViewType::e2D, vk::Format::eR8G8B8A8Srgb,
            {}, {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}});

    {
        vk::DescriptorImageInfo imageInfo{*this->dummySampler, *this->dummyImageView, vk::ImageLayout::eShaderReadOnlyOptimal};
        vk::WriteDescriptorSet writeDesc{**this->descSet, 0, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo, nullptr, nullptr};
        this->device->updateDescriptorSets(writeDesc, nullptr);
    }
    // 确保字体描述符集指向重建后的 ImageView
    if (this->fontDescSet) {
        vk::DescriptorImageInfo imageInfo{*this->dummySampler, *this->dummyImageView, vk::ImageLayout::eShaderReadOnlyOptimal};
        vk::WriteDescriptorSet writeDesc{**this->fontDescSet, 0, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo, nullptr, nullptr};
        this->device->updateDescriptorSets(writeDesc, nullptr);
    }

    textureBuilt = true;
    return *this;
}

} // namespace youklx