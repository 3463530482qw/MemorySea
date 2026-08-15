namespace youklx {
    // 绑定渲染端并创建图集贴图(首次绘制时由字体渲染管线调用一次)
    void Font::bindRenderer(
        vk::raii::PhysicalDevice& pd, vk::raii::Device& dev,                
        vk::raii::DescriptorSetLayout& layout, vk::raii::DescriptorPool& pool,     
        vk::raii::Sampler& samp, uint32_t queueFamilyIndex
    ) {
        physicalDevice = &pd;
        device = &dev;
        descLayout = *layout;   // raii 单解引用即句柄
        descPool = *pool;
        sampler = *samp;
        graphicsFamilyIndex = queueFamilyIndex;
        createAtlasImage();

        // 从共享池分配描述符集(raii 移动持有所有权,析构时释放回池)
        vk::DescriptorSetAllocateInfo setInfo;
        setInfo.setDescriptorPool(descPool);
        setInfo.setDescriptorSetCount(1);
        vk::DescriptorSetLayout layoutHandle = descLayout;
        setInfo.setPSetLayouts(&layoutHandle);
        descSet = std::move(vk::raii::DescriptorSets(*device, setInfo)[0]);

        // 写入描述符(图集视图 + 采样器)
        vk::DescriptorImageInfo imageInfo;
        imageInfo.setImageLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
        imageInfo.setImageView(*atlasView);
        imageInfo.setSampler(sampler);
        vk::WriteDescriptorSet write;
        write.setDstSet(descSet);
        write.setDstBinding(0);
        write.setDstArrayElement(0);
        write.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        write.setDescriptorCount(1);
        write.setPImageInfo(&imageInfo);
        device->updateDescriptorSets({write}, {});
    }

    bool Font::rendererBound() const {
        return device != nullptr;
    }

    vk::DescriptorSet Font::descriptorSet() const {
        return descSet;
    }

    // 按 atlasW/H 创建图集图像+视图+内存(绑定与重建共用)
    void Font::createAtlasImage() {
        vk::ImageCreateInfo imgInfo;
        imgInfo.setImageType(vk::ImageType::e2D);
        imgInfo.setExtent(vk::Extent3D{static_cast<uint32_t>(atlasW), static_cast<uint32_t>(atlasH), 1});
        imgInfo.setMipLevels(1);
        imgInfo.setArrayLayers(1);
        imgInfo.setFormat(vk::Format::eR8Unorm);          // A8 alpha 图
        imgInfo.setTiling(vk::ImageTiling::eOptimal);
        imgInfo.setInitialLayout(vk::ImageLayout::eUndefined);
        imgInfo.setUsage(vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled);
        imgInfo.setSharingMode(vk::SharingMode::eExclusive);
        imgInfo.setSamples(vk::SampleCountFlagBits::e1);
        atlasImage = vk::raii::Image(*device, imgInfo);

        vk::MemoryRequirements memReq = atlasImage.getMemoryRequirements();
        vk::MemoryAllocateInfo allocInfo;
        allocInfo.setAllocationSize(memReq.size);
        allocInfo.setMemoryTypeIndex(findMemoryType(*physicalDevice, memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal));
        atlasMemory = vk::raii::DeviceMemory(*device, allocInfo);
        atlasImage.bindMemory(*atlasMemory, 0);

        vk::ImageViewCreateInfo viewInfo;
        viewInfo.setImage(*atlasImage);
        viewInfo.setViewType(vk::ImageViewType::e2D);
        viewInfo.setFormat(vk::Format::eR8Unorm);
        viewInfo.setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
        atlasView = vk::raii::ImageView(*device, viewInfo);
    }
}
