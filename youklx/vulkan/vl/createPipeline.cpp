namespace youklx {

// 顶点结构：2D位置 + RGBA颜色
struct Vertex {
    float x, y;
    float r, g, b, a;

    static vk::VertexInputBindingDescription getBindingDescription() {
        return {0, sizeof(Vertex), vk::VertexInputRate::eVertex};
    }

    static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions() {
        return {{
            {0, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, x)},
            {1, 0, vk::Format::eR32G32B32A32Sfloat, offsetof(Vertex, r)}
        }};
    }
};

// 从文件读取 SPIR-V 字节码（尝试多个搜索路径）
static std::vector<uint32_t> readSpv(const std::string& filename) {
    const std::vector<std::string> searchPaths = {
        "build/shaders/" + filename,
        "shaders/" + filename,
        "../build/shaders/" + filename,
    };
    for (const auto& path : searchPaths) {
        std::ifstream file(path, std::ios::ate | std::ios::binary);
        if (file.is_open()) {
            size_t fileSize = static_cast<size_t>(file.tellg());
            file.seekg(0);
            std::vector<uint32_t> buffer(fileSize / sizeof(uint32_t));
            file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
            file.close();
            return buffer;
        }
    }
    throw std::runtime_error("无法打开着色器文件: " + filename);
}

Vulkan& Vulkan::createPipeline() {
    auto vertCode = readSpv("shader.vert.spv");
    auto fragCode = readSpv("shader.frag.spv");

    vk::raii::ShaderModule vertModule(*this->device,
        vk::ShaderModuleCreateInfo{{}, vertCode.size() * sizeof(uint32_t), vertCode.data()});
    vk::raii::ShaderModule fragModule(*this->device,
        vk::ShaderModuleCreateInfo{{}, fragCode.size() * sizeof(uint32_t), fragCode.data()});

    vk::PipelineShaderStageCreateInfo vertStage{
        {}, vk::ShaderStageFlagBits::eVertex, *vertModule, "main"};
    vk::PipelineShaderStageCreateInfo fragStage{
        {}, vk::ShaderStageFlagBits::eFragment, *fragModule, "main"};
    vk::PipelineShaderStageCreateInfo stages[] = {vertStage, fragStage};

    auto bindingDesc = Vertex::getBindingDescription();
    auto attrDescs = Vertex::getAttributeDescriptions();
    vk::PipelineVertexInputStateCreateInfo vertexInput{
        {}, 1, &bindingDesc,
        static_cast<uint32_t>(attrDescs.size()), attrDescs.data()
    };

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{
        {}, vk::PrimitiveTopology::eTriangleStrip, VK_FALSE};

    std::vector<vk::DynamicState> dynamics = {
        vk::DynamicState::eViewport, vk::DynamicState::eScissor};
    vk::PipelineDynamicStateCreateInfo dynamicState{{}, dynamics};

    vk::PipelineViewportStateCreateInfo viewportState{{}, 1, nullptr, 1, nullptr};

    // rasterizer：无剔除（2D 线条无需背面剔除）
    vk::PipelineRasterizationStateCreateInfo rasterizer{
        {}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill,
        vk::CullModeFlagBits::eNone, vk::FrontFace::eCounterClockwise,
        VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f};

    vk::PipelineMultisampleStateCreateInfo multisampling{};

    vk::PipelineColorBlendAttachmentState blendAttachment{};
    blendAttachment.blendEnable = VK_TRUE;
    blendAttachment.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
    blendAttachment.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
    blendAttachment.colorBlendOp = vk::BlendOp::eAdd;
    blendAttachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    blendAttachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
    blendAttachment.alphaBlendOp = vk::BlendOp::eAdd;
    blendAttachment.colorWriteMask =
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    vk::PipelineColorBlendStateCreateInfo colorBlending{
        {}, VK_FALSE, vk::LogicOp::eCopy, 1, &blendAttachment};

    vk::PushConstantRange pushRange{
        vk::ShaderStageFlagBits::eVertex, 0, sizeof(float) * 16};
    vk::PipelineLayoutCreateInfo layoutInfo{{}, 0, nullptr, 1, &pushRange};
    this->pipelineLayout.emplace(*this->device, layoutInfo);

    vk::GraphicsPipelineCreateInfo pipelineInfo{
        {}, 2, stages, &vertexInput, &inputAssembly, nullptr,
        &viewportState, &rasterizer, &multisampling, nullptr,
        &colorBlending, &dynamicState, *this->pipelineLayout,
        *this->renderPass, 0};
    this->graphicsPipeline.emplace(*this->device, nullptr, pipelineInfo);

    return *this;
}
}