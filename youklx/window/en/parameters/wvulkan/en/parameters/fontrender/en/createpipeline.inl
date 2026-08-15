namespace youklx {
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

        // 顶点输入:Vertex{x,y,u,v,r,g,b,a, ow,aa,占位, 描边色}
        // → pos(2)+uv(2)+color(4)+effects(4)+outline(4),共 64 字节
        vk::VertexInputBindingDescription bindingDesc;
        bindingDesc.setBinding(0);
        bindingDesc.setStride(sizeof(Vertex));
        bindingDesc.setInputRate(vk::VertexInputRate::eVertex);

        std::array<vk::VertexInputAttributeDescription, 5> attrs;
        attrs[0].setLocation(0); attrs[0].setBinding(0); attrs[0].setFormat(vk::Format::eR32G32Sfloat); attrs[0].setOffset(0);
        attrs[1].setLocation(1); attrs[1].setBinding(0); attrs[1].setFormat(vk::Format::eR32G32Sfloat); attrs[1].setOffset(2 * sizeof(float));
        attrs[2].setLocation(2); attrs[2].setBinding(0); attrs[2].setFormat(vk::Format::eR32G32B32A32Sfloat); attrs[2].setOffset(4 * sizeof(float));
        attrs[3].setLocation(3); attrs[3].setBinding(0); attrs[3].setFormat(vk::Format::eR32G32B32A32Sfloat); attrs[3].setOffset(8 * sizeof(float));
        attrs[4].setLocation(4); attrs[4].setBinding(0); attrs[4].setFormat(vk::Format::eR32G32B32A32Sfloat); attrs[4].setOffset(12 * sizeof(float));

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
}
