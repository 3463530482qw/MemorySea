namespace youklx {

// 最小顶点着色器（SPIR-V）：直接输出一个顶点，但不产生任何三角形
static const uint32_t vertSpv[] = {
    0x07230203,0x00010000,0x00080001,0x0000000c,
    0x00000000,0x00020011,0x00000001,0x0006000b,
    0x00000001,0x4c534c47,0x6474732e,0x3035342e,
    0x00000000,0x0003000e,0x00000000,0x00000001,
    0x0007000f,0x00000000,0x00000004,0x6e69616d,
    0x00000000
};

// 最小片段着色器（SPIR-V）：不输出任何颜色，依赖清屏颜色
static const uint32_t fragSpv[] = {
    0x07230203,0x00010000,0x00080001,0x0000000e,
    0x00000000,0x00020011,0x00000001,0x0006000b,
    0x00000001,0x4c534c47,0x6474732e,0x3035342e,
    0x00000000,0x0003000e,0x00000000,0x00000001,
    0x0007000f,0x00000004,0x00000004,0x6e69616d,
    0x00000000,0x00030010,0x00000004,0x00000007
};

Vulkan& Vulkan::createPipeline() {
    // 1. 从内嵌数组创建着色器模块
    vk::raii::ShaderModule vertModule(*this->device,
        vk::ShaderModuleCreateInfo{{}, sizeof(vertSpv), vertSpv});
    vk::raii::ShaderModule fragModule(*this->device,
        vk::ShaderModuleCreateInfo{{}, sizeof(fragSpv), fragSpv});

    // 2. 着色器阶段
    vk::PipelineShaderStageCreateInfo vertStage{
        {}, vk::ShaderStageFlagBits::eVertex, *vertModule, "main"};
    vk::PipelineShaderStageCreateInfo fragStage{
        {}, vk::ShaderStageFlagBits::eFragment, *fragModule, "main"};
    vk::PipelineShaderStageCreateInfo stages[] = {vertStage, fragStage};

    // 3. 顶点输入、输入装配
    vk::PipelineVertexInputStateCreateInfo vertexInput{};
    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{
        {}, vk::PrimitiveTopology::eTriangleList, VK_FALSE};

    // 4. 动态状态
    std::vector<vk::DynamicState> dynamics = {
        vk::DynamicState::eViewport, vk::DynamicState::eScissor};
    vk::PipelineDynamicStateCreateInfo dynamicState{{}, dynamics};

    // 5. 视口、光栅化、多重采样
    vk::PipelineViewportStateCreateInfo viewportState{{}, 1, nullptr, 1, nullptr};
    vk::PipelineRasterizationStateCreateInfo rasterizer{
        {}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill,
        vk::CullModeFlagBits::eBack, vk::FrontFace::eClockwise,
        VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f};
    vk::PipelineMultisampleStateCreateInfo multisampling{};

    // 6. 颜色混合
    vk::PipelineColorBlendAttachmentState blendAttachment{};
    blendAttachment.colorWriteMask = 
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    vk::PipelineColorBlendStateCreateInfo colorBlending{
        {}, VK_FALSE, vk::LogicOp::eCopy, 1, &blendAttachment};

    // 7. 管线布局
    vk::PipelineLayoutCreateInfo layoutInfo{};
    this->pipelineLayout.emplace(*this->device, layoutInfo);

    // 8. 创建管线
    vk::GraphicsPipelineCreateInfo pipelineInfo{
        {}, 2, stages, &vertexInput, &inputAssembly, nullptr,
        &viewportState, &rasterizer, &multisampling, nullptr,
        &colorBlending, &dynamicState, *this->pipelineLayout,
        *this->renderPass, 0};
    this->graphicsPipeline.emplace(*this->device, nullptr, pipelineInfo);

    return *this;
}
}