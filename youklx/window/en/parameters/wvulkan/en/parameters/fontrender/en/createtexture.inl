namespace youklx {
    // --- 图集纹理(初始空,draw 时按需上传) ---
    void FontRender::createTexture() {
        // 重建图像 + 视图 + 内存(尺寸按字体当前图集尺寸)
        recreateTexture();

        // 采样器
        vk::SamplerCreateInfo sampInfo;
        sampInfo.setMagFilter(vk::Filter::eLinear);
        sampInfo.setMinFilter(vk::Filter::eLinear);
        sampInfo.setAddressModeU(vk::SamplerAddressMode::eClampToEdge);
        sampInfo.setAddressModeV(vk::SamplerAddressMode::eClampToEdge);
        sampInfo.setAddressModeW(vk::SamplerAddressMode::eClampToEdge);
        sampInfo.setMipmapMode(vk::SamplerMipmapMode::eNearest);
        sampInfo.setAnisotropyEnable(false);
        sampler = vk::raii::Sampler(*device, sampInfo);

        // 描述符集布局(set=0 binding=0 combined image sampler,与 font.frag 一致)
        vk::DescriptorSetLayoutBinding binding;
        binding.setBinding(0);
        binding.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        binding.setDescriptorCount(1);
        binding.setStageFlags(vk::ShaderStageFlagBits::eFragment);
        vk::DescriptorSetLayoutCreateInfo descLayoutInfo;
        descLayoutInfo.setBindingCount(1);
        descLayoutInfo.setPBindings(&binding);
        descLayout = vk::raii::DescriptorSetLayout(*device, descLayoutInfo);

        // 描述符池
        vk::DescriptorPoolSize poolSize;
        poolSize.setType(vk::DescriptorType::eCombinedImageSampler);
        poolSize.setDescriptorCount(1);
        vk::DescriptorPoolCreateInfo poolInfo;
        poolInfo.setMaxSets(1);
        poolInfo.setPoolSizeCount(1);
        poolInfo.setPPoolSizes(&poolSize);
        descPool = vk::raii::DescriptorPool(*device, poolInfo);

        // 描述符集 + 写入
        vk::DescriptorSetAllocateInfo setInfo;
        setInfo.setDescriptorPool(*descPool);
        setInfo.setDescriptorSetCount(1);
        vk::DescriptorSetLayout layoutHandle = *descLayout;
        setInfo.setPSetLayouts(&layoutHandle);
        descSet = std::move(vk::raii::DescriptorSets(*device, setInfo)[0]);

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
