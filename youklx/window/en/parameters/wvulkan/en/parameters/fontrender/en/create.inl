namespace youklx {
    uint32_t FontRender::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags flags) const {
        vk::PhysicalDeviceMemoryProperties props = physicalDevice->getMemoryProperties();
        for (uint32_t i = 0; i < props.memoryTypeCount; i++) {
            if ((typeFilter & (1u << i)) && (props.memoryTypes[i].propertyFlags & flags) == flags)
                return i;
        }
        throw std::runtime_error("未找到满足要求的内存类型");
    }

    void FontRender::init(vk::raii::PhysicalDevice& pd, vk::raii::Device& dev, vk::raii::RenderPass& rp, vk::Format& fmt, vk::Extent2D& ext, Font* fot, uint32_t queueFamilyIndex) {
        physicalDevice = &pd;
        device = &dev;
        renderPass = &rp;
        format = &fmt;
        extent = &ext;
        font = fot;
        graphicsFamilyIndex = queueFamilyIndex;
        createTexture();
        createPipeline();
        createVertexBuffer();
    }

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

    // --- 图形管线(font.vert.spv / font.frag.spv) ---
    void FontRender::createPipeline() {
        auto readFile = [](const char* name) {
            // 兼容两种运行目录:根目录(build/shaders/)与 build/(shaders/)
            std::vector<std::string> candidates{std::string("build/shaders/") + name, std::string("shaders/") + name};
            for (const auto& path : candidates) {
                std::ifstream file(path, std::ios::binary | std::ios::ate);
                if (file.is_open()) {
                    std::streamsize sz = file.tellg();
                    file.seekg(0, std::ios::beg);
                    std::vector<char> buf(sz);
                    file.read(buf.data(), sz);
                    return buf;
                }
            }
            throw std::runtime_error(std::string("无法打开着色器: ") + name);
        };
        auto readSpirV = [&](const char* path, std::vector<uint32_t>& out) {
            std::vector<char> buf = readFile(path);
            out.resize(buf.size() / 4);
            std::memcpy(out.data(), buf.data(), buf.size());
        };
        std::vector<uint32_t> vertCode, fragCode;
        readSpirV("font.vert.spv", vertCode);
        readSpirV("font.frag.spv", fragCode);
        vk::ShaderModuleCreateInfo vertInfo;
        vertInfo.setCodeSize(vertCode.size() * sizeof(uint32_t));
        vertInfo.setPCode(vertCode.data());
        vk::raii::ShaderModule vertShader(*device, vertInfo);
        vk::ShaderModuleCreateInfo fragInfo;
        fragInfo.setCodeSize(fragCode.size() * sizeof(uint32_t));
        fragInfo.setPCode(fragCode.data());
        vk::raii::ShaderModule fragShader(*device, fragInfo);

        vk::PipelineShaderStageCreateInfo stages[2];
        stages[0].setStage(vk::ShaderStageFlagBits::eVertex);
        stages[0].setModule(*vertShader);
        stages[0].setPName("main");
        stages[1].setStage(vk::ShaderStageFlagBits::eFragment);
        stages[1].setModule(*fragShader);
        stages[1].setPName("main");

        // 顶点输入:Vertex{x,y,u,v,r,g,b,a} → pos(2)+uv(2)+color(4)
        vk::VertexInputBindingDescription bindingDesc;
        bindingDesc.setBinding(0);
        bindingDesc.setStride(sizeof(Vertex));
        bindingDesc.setInputRate(vk::VertexInputRate::eVertex);

        std::array<vk::VertexInputAttributeDescription, 3> attrs;
        attrs[0].setLocation(0); attrs[0].setBinding(0); attrs[0].setFormat(vk::Format::eR32G32Sfloat); attrs[0].setOffset(0);
        attrs[1].setLocation(1); attrs[1].setBinding(0); attrs[1].setFormat(vk::Format::eR32G32Sfloat); attrs[1].setOffset(2 * sizeof(float));
        attrs[2].setLocation(2); attrs[2].setBinding(0); attrs[2].setFormat(vk::Format::eR32G32B32A32Sfloat); attrs[2].setOffset(4 * sizeof(float));

        vk::PipelineVertexInputStateCreateInfo vertexInput;
        vertexInput.setVertexBindingDescriptionCount(1);
        vertexInput.setPVertexBindingDescriptions(&bindingDesc);
        vertexInput.setVertexAttributeDescriptionCount(static_cast<uint32_t>(attrs.size()));
        vertexInput.setPVertexAttributeDescriptions(attrs.data());

        vk::PipelineInputAssemblyStateCreateInfo inputAssembly;
        inputAssembly.setTopology(vk::PrimitiveTopology::eTriangleList);
        inputAssembly.setPrimitiveRestartEnable(false);

        vk::PipelineViewportStateCreateInfo viewportState;
        viewportState.setViewportCount(1);
        viewportState.setScissorCount(1);   // 动态视口/裁剪

        vk::PipelineRasterizationStateCreateInfo rasterizer;
        rasterizer.setDepthClampEnable(false);
        rasterizer.setRasterizerDiscardEnable(false);
        rasterizer.setPolygonMode(vk::PolygonMode::eFill);
        rasterizer.setLineWidth(1.0f);
        rasterizer.setCullMode(vk::CullModeFlagBits::eNone);
        rasterizer.setFrontFace(vk::FrontFace::eClockwise);
        rasterizer.setDepthBiasEnable(false);

        vk::PipelineMultisampleStateCreateInfo multisample;
        multisample.setSampleShadingEnable(false);
        multisample.setRasterizationSamples(vk::SampleCountFlagBits::e1);

        vk::PipelineColorBlendAttachmentState blendAttach;
        blendAttach.setBlendEnable(true);
        blendAttach.setSrcColorBlendFactor(vk::BlendFactor::eSrcAlpha);
        blendAttach.setDstColorBlendFactor(vk::BlendFactor::eOneMinusSrcAlpha);
        blendAttach.setColorBlendOp(vk::BlendOp::eAdd);
        blendAttach.setSrcAlphaBlendFactor(vk::BlendFactor::eOne);
        blendAttach.setDstAlphaBlendFactor(vk::BlendFactor::eZero);
        blendAttach.setAlphaBlendOp(vk::BlendOp::eAdd);
        blendAttach.setColorWriteMask(vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG
            | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA);

        vk::PipelineColorBlendStateCreateInfo colorBlend;
        colorBlend.setLogicOpEnable(false);
        colorBlend.setAttachmentCount(1);
        colorBlend.setPAttachments(&blendAttach);

        std::array<vk::DynamicState, 2> dynStates{vk::DynamicState::eViewport, vk::DynamicState::eScissor};
        vk::PipelineDynamicStateCreateInfo dynamicState;
        dynamicState.setDynamicStateCount(static_cast<uint32_t>(dynStates.size()));
        dynamicState.setPDynamicStates(dynStates.data());

        // push constants: mat4 mvp + 3 float(与 font.vert 一致, 64+12=76B)
        vk::PushConstantRange pcRange;
        pcRange.setStageFlags(vk::ShaderStageFlagBits::eVertex);
        pcRange.setOffset(0);
        pcRange.setSize(76);

        vk::PipelineLayoutCreateInfo layoutInfo;
        layoutInfo.setSetLayoutCount(1);
        layoutInfo.setPSetLayouts(&*descLayout);
        layoutInfo.setPushConstantRangeCount(1);
        layoutInfo.setPPushConstantRanges(&pcRange);
        pipelineLayout = vk::raii::PipelineLayout(*device, layoutInfo);

        vk::GraphicsPipelineCreateInfo pipeInfo;
        pipeInfo.setStageCount(2);
        pipeInfo.setPStages(stages);
        pipeInfo.setPVertexInputState(&vertexInput);
        pipeInfo.setPInputAssemblyState(&inputAssembly);
        pipeInfo.setPViewportState(&viewportState);
        pipeInfo.setPRasterizationState(&rasterizer);
        pipeInfo.setPMultisampleState(&multisample);
        pipeInfo.setPColorBlendState(&colorBlend);
        pipeInfo.setPDynamicState(&dynamicState);
        pipeInfo.setLayout(*pipelineLayout);
        pipeInfo.setRenderPass(**renderPass);
        pipeline = vk::raii::Pipeline(*device, nullptr, pipeInfo);
    }

    // --- 顶点缓冲(host-visible,双缓冲,每帧交替 memcpy) ---
    void FontRender::createVertexBuffer() {
        vk::BufferCreateInfo bufInfo;
        bufInfo.setSize(1024 * 1024);                     // 1MB 预分配
        bufInfo.setUsage(vk::BufferUsageFlagBits::eVertexBuffer);
        bufInfo.setSharingMode(vk::SharingMode::eExclusive);
        for (int i = 0; i < 2; i++) {
            vertexBuffer[i] = vk::raii::Buffer(*device, bufInfo);
            vk::MemoryRequirements memReq = vertexBuffer[i].getMemoryRequirements();
            vk::MemoryAllocateInfo allocInfo;
            allocInfo.setAllocationSize(memReq.size);
            allocInfo.setMemoryTypeIndex(findMemoryType(memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));
            vertexMemory[i] = vk::raii::DeviceMemory(*device, allocInfo);
            vertexBuffer[i].bindMemory(*vertexMemory[i], 0);
        }
    }
}
