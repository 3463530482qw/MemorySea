namespace youklx {
    // 描述符集数量上限(每个字体一张图集一套描述符集,超出报错)
    constexpr uint32_t fontDescriptorSets = 64;

    // --- 描述符配套资源:布局(set=0 binding=0 combined image sampler,与 font.frag 一致)+ 池 + 采样器 ---
    void FontRender::createDescriptors() {
        vk::DescriptorSetLayoutBinding binding;
        binding.setBinding(0);
        binding.setDescriptorType(vk::DescriptorType::eCombinedImageSampler);
        binding.setDescriptorCount(1);
        binding.setStageFlags(vk::ShaderStageFlagBits::eFragment);
        vk::DescriptorSetLayoutCreateInfo descLayoutInfo;
        descLayoutInfo.setBindingCount(1);
        descLayoutInfo.setPBindings(&binding);
        descLayout = vk::raii::DescriptorSetLayout(*device, descLayoutInfo);

        vk::DescriptorPoolSize poolSize;
        poolSize.setType(vk::DescriptorType::eCombinedImageSampler);
        poolSize.setDescriptorCount(fontDescriptorSets);
        vk::DescriptorPoolCreateInfo poolInfo;
        poolInfo.setMaxSets(fontDescriptorSets);
        poolInfo.setPoolSizeCount(1);
        poolInfo.setPPoolSizes(&poolSize);
        descPool = vk::raii::DescriptorPool(*device, poolInfo);

        // 字体图集统一采样方式:线性过滤+边缘钳制
        vk::SamplerCreateInfo sampInfo;
        sampInfo.setMagFilter(vk::Filter::eLinear);
        sampInfo.setMinFilter(vk::Filter::eLinear);
        sampInfo.setAddressModeU(vk::SamplerAddressMode::eClampToEdge);
        sampInfo.setAddressModeV(vk::SamplerAddressMode::eClampToEdge);
        sampInfo.setAddressModeW(vk::SamplerAddressMode::eClampToEdge);
        sampInfo.setMipmapMode(vk::SamplerMipmapMode::eNearest);
        sampInfo.setAnisotropyEnable(false);
        sampler = vk::raii::Sampler(*device, sampInfo);
    }
}
