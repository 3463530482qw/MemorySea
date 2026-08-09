namespace youklx {
    // --- 重建图集图像 + 视图 + 内存(尺寸变化时调用),并更新描述符 ---
    void FontRender::recreateTexture() {
        int aw = font ? font->atlasW : 1024;
        int ah = font ? font->atlasH : 1024;

        // 图集图像
        vk::ImageCreateInfo imgInfo;
        imgInfo.setImageType(vk::ImageType::e2D);
        imgInfo.setExtent(vk::Extent3D{static_cast<uint32_t>(aw), static_cast<uint32_t>(ah), 1});
        imgInfo.setMipLevels(1);
        imgInfo.setArrayLayers(1);
        imgInfo.setFormat(vk::Format::eR8Unorm);          // A8 alpha 图
        imgInfo.setTiling(vk::ImageTiling::eOptimal);
        imgInfo.setInitialLayout(vk::ImageLayout::eUndefined);
        imgInfo.setUsage(vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled);
        imgInfo.setSharingMode(vk::SharingMode::eExclusive);
        imgInfo.setSamples(vk::SampleCountFlagBits::e1);
        atlasImage = vk::raii::Image(*device, imgInfo);

        // 内存
        vk::MemoryRequirements memReq = atlasImage.getMemoryRequirements();
        vk::MemoryAllocateInfo allocInfo;
        allocInfo.setAllocationSize(memReq.size);
        allocInfo.setMemoryTypeIndex(findMemoryType(memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal));
        atlasMemory = vk::raii::DeviceMemory(*device, allocInfo);
        atlasImage.bindMemory(*atlasMemory, 0);

        // 图像视图
        vk::ImageViewCreateInfo viewInfo;
        viewInfo.setImage(*atlasImage);
        viewInfo.setViewType(vk::ImageViewType::e2D);
        viewInfo.setFormat(vk::Format::eR8Unorm);
        viewInfo.setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
        atlasView = vk::raii::ImageView(*device, viewInfo);

        // 更新描述符(描述符集已存在时)
        if (descSet != nullptr) {
            vk::DescriptorImageInfo imageInfo;
            imageInfo.setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
            imageInfo.setImageView(*atlasView);
            imageInfo.setSampler(*sampler);
            vk::WriteDescriptorSet write;
            write.setDstSet(*descSet);
            write.setDstBinding(0);
            write.setDstArrayElement(0);
            write.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
            write.setDescriptorCount(1);
            write.setPImageInfo(&imageInfo);
            device->updateDescriptorSets({write}, {});
        }
    }
}
