namespace youklx {

struct Vertex {
    float x, y, u, v, r, g, b, a;
    static vk::VertexInputBindingDescription getBindingDescription() {
        return {0, sizeof(Vertex), vk::VertexInputRate::eVertex};
    }
    static std::array<vk::VertexInputAttributeDescription, 3> getAttributeDescriptions() {
        return {{
            {0, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, x)},
            {1, 0, vk::Format::eR32G32Sfloat, offsetof(Vertex, u)},
            {2, 0, vk::Format::eR32G32B32A32Sfloat, offsetof(Vertex, r)}
        }};
    }
};

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
    // 共用顶点输入
    auto bindingDesc = Vertex::getBindingDescription();
    auto attrDescs = Vertex::getAttributeDescriptions();
    vk::PipelineVertexInputStateCreateInfo vertexInput{
        {}, 1, &bindingDesc,
        static_cast<uint32_t>(attrDescs.size()), attrDescs.data()};

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly{
        {}, vk::PrimitiveTopology::eTriangleStrip, VK_FALSE};

    std::vector<vk::DynamicState> dynamics = {
        vk::DynamicState::eViewport, vk::DynamicState::eScissor};
    vk::PipelineDynamicStateCreateInfo dynamicState{{}, dynamics};
    vk::PipelineViewportStateCreateInfo viewportState{{}, 1, nullptr, 1, nullptr};

    vk::PipelineRasterizationStateCreateInfo rasterizer{
        {}, VK_FALSE, VK_FALSE, vk::PolygonMode::eFill,
        vk::CullModeFlagBits::eNone, vk::FrontFace::eCounterClockwise,
        VK_FALSE, 0.0f, 0.0f, 0.0f, 1.0f};

    vk::PipelineMultisampleStateCreateInfo multisampling{};

    // 线条混合状态：Alpha混合
    vk::PipelineColorBlendAttachmentState lineBlend{};
    lineBlend.blendEnable = VK_TRUE;
    lineBlend.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
    lineBlend.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
    lineBlend.colorBlendOp = vk::BlendOp::eAdd;
    lineBlend.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    lineBlend.dstAlphaBlendFactor = vk::BlendFactor::eZero;
    lineBlend.alphaBlendOp = vk::BlendOp::eAdd;
    lineBlend.colorWriteMask =
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    vk::PipelineColorBlendStateCreateInfo lineBlending{
        {}, VK_FALSE, vk::LogicOp::eCopy, 1, &lineBlend};

    // 图片混合状态：覆盖模式（直接覆盖，不混合）
    vk::PipelineColorBlendAttachmentState imageBlend{};
    imageBlend.blendEnable = VK_FALSE;
    imageBlend.colorWriteMask =
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    vk::PipelineColorBlendStateCreateInfo imageBlending{
        {}, VK_FALSE, vk::LogicOp::eCopy, 1, &imageBlend};

    // 字体混合状态：Alpha混合（保留透明度）
    vk::PipelineColorBlendAttachmentState fontBlend{};
    fontBlend.blendEnable = VK_TRUE;
    fontBlend.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
    fontBlend.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
    fontBlend.colorBlendOp = vk::BlendOp::eAdd;
    fontBlend.srcAlphaBlendFactor = vk::BlendFactor::eOne;
    fontBlend.dstAlphaBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
    fontBlend.alphaBlendOp = vk::BlendOp::eAdd;
    fontBlend.colorWriteMask =
        vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
        vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    vk::PipelineColorBlendStateCreateInfo fontBlending{
        {}, VK_FALSE, vk::LogicOp::eCopy, 1, &fontBlend};

    // 描述符布局
    vk::DescriptorSetLayoutBinding samplerBinding{
        0, vk::DescriptorType::eCombinedImageSampler, 1,
        vk::ShaderStageFlagBits::eFragment, nullptr};
    this->descSetLayout.emplace(*this->device,
        vk::DescriptorSetLayoutCreateInfo{{}, 1, &samplerBinding});

    const vk::DescriptorSetLayout& dsl = **this->descSetLayout;
    vk::PushConstantRange pushRange{
        vk::ShaderStageFlagBits::eVertex, 0, sizeof(float) * 16};
    vk::PipelineLayoutCreateInfo layoutInfo{{}, dsl, pushRange};
    this->pipelineLayout.emplace(*this->device, layoutInfo);

    // ===== 线条管线 (line.vert.spv + line.frag.spv) =====
    {
        auto lv = readSpv("line.vert.spv");
        auto lf = readSpv("line.frag.spv");
        vk::raii::ShaderModule vm{*this->device,
            vk::ShaderModuleCreateInfo{{}, lv.size() * sizeof(uint32_t), lv.data()}};
        vk::raii::ShaderModule fm{*this->device,
            vk::ShaderModuleCreateInfo{{}, lf.size() * sizeof(uint32_t), lf.data()}};
        vk::PipelineShaderStageCreateInfo vs{{}, vk::ShaderStageFlagBits::eVertex, *vm, "main"};
        vk::PipelineShaderStageCreateInfo fs{{}, vk::ShaderStageFlagBits::eFragment, *fm, "main"};
        vk::PipelineShaderStageCreateInfo ss[] = {vs, fs};
        vk::GraphicsPipelineCreateInfo pi{{}, 2, ss, &vertexInput, &inputAssembly, nullptr,
            &viewportState, &rasterizer, &multisampling, nullptr,
            &lineBlending, &dynamicState, *this->pipelineLayout, *this->renderPass, 0};
        this->graphicsPipeline.emplace(*this->device, nullptr, pi);
    }

    // ===== 图片管线 (image.vert.spv + image.frag.spv) =====
    {
        auto iv = readSpv("image.vert.spv");
        auto _if = readSpv("image.frag.spv");
        vk::raii::ShaderModule vm{*this->device,
            vk::ShaderModuleCreateInfo{{}, iv.size() * sizeof(uint32_t), iv.data()}};
        vk::raii::ShaderModule fm{*this->device,
            vk::ShaderModuleCreateInfo{{}, _if.size() * sizeof(uint32_t), _if.data()}};
        vk::PipelineShaderStageCreateInfo vs{{}, vk::ShaderStageFlagBits::eVertex, *vm, "main"};
        vk::PipelineShaderStageCreateInfo fs{{}, vk::ShaderStageFlagBits::eFragment, *fm, "main"};
        vk::PipelineShaderStageCreateInfo ss[] = {vs, fs};
        vk::GraphicsPipelineCreateInfo pi{{}, 2, ss, &vertexInput, &inputAssembly, nullptr,
            &viewportState, &rasterizer, &multisampling, nullptr,
            &imageBlending, &dynamicState, *this->pipelineLayout, *this->renderPass, 0};
        this->graphicsPipelineImage.emplace(*this->device, nullptr, pi);
    }

    // ===== 字体管线 (font.vert.spv + font.frag.spv) =====
    // 字体使用 TriangleList 避免字符间退化三角形连接
    {
        vk::PipelineInputAssemblyStateCreateInfo fontInputAssembly{
            {}, vk::PrimitiveTopology::eTriangleList, VK_FALSE};
        auto fv = readSpv("font.vert.spv");
        auto ff = readSpv("font.frag.spv");
        vk::raii::ShaderModule vm{*this->device,
            vk::ShaderModuleCreateInfo{{}, fv.size() * sizeof(uint32_t), fv.data()}};
        vk::raii::ShaderModule fm{*this->device,
            vk::ShaderModuleCreateInfo{{}, ff.size() * sizeof(uint32_t), ff.data()}};
        vk::PipelineShaderStageCreateInfo vs{{}, vk::ShaderStageFlagBits::eVertex, *vm, "main"};
        vk::PipelineShaderStageCreateInfo fs{{}, vk::ShaderStageFlagBits::eFragment, *fm, "main"};
        vk::PipelineShaderStageCreateInfo ss[] = {vs, fs};
        vk::GraphicsPipelineCreateInfo pi{{}, 2, ss, &vertexInput, &fontInputAssembly, nullptr,
            &viewportState, &rasterizer, &multisampling, nullptr,
            &fontBlending, &dynamicState, *this->pipelineLayout, *this->renderPass, 0};
        this->graphicsPipelineFont.emplace(*this->device, nullptr, pi);
    }

    // ===== 默认 1×1 白色纹理 =====
    uint8_t white[4] = {255, 255, 255, 255};
    vk::DeviceSize imgSize = 4;
    vk::BufferCreateInfo stagingInfo{{}, imgSize, vk::BufferUsageFlagBits::eTransferSrc};
    vk::raii::Buffer stagingBuf{*this->device, stagingInfo};
    auto stagingReqs = stagingBuf.getMemoryRequirements();
    vk::raii::DeviceMemory stagingMem{*this->device,
        vk::MemoryAllocateInfo{stagingReqs.size,
            findMemoryType(stagingReqs.memoryTypeBits,
                vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent)}};
    stagingBuf.bindMemory(*stagingMem, 0);
    void* ptr = stagingMem.mapMemory(0, imgSize);
    memcpy(ptr, white, imgSize);
    stagingMem.unmapMemory();

    vk::ImageCreateInfo imgInfo{{}, vk::ImageType::e2D, vk::Format::eR8G8B8A8Srgb,
        {1, 1, 1}, 1, 1, vk::SampleCountFlagBits::e1,
        vk::ImageTiling::eOptimal, vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled};
    this->dummyImage.emplace(*this->device, imgInfo);
    auto imgReqs = this->dummyImage->getMemoryRequirements();
    this->dummyImageMemory.emplace(*this->device,
        vk::MemoryAllocateInfo{imgReqs.size, findMemoryType(imgReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)});
    this->dummyImage->bindMemory(*this->dummyImageMemory, 0);

    vk::raii::CommandBuffer copyCmd = std::move(
        this->device->allocateCommandBuffers(vk::CommandBufferAllocateInfo{*this->commandPool, vk::CommandBufferLevel::ePrimary, 1}).front());
    copyCmd.begin(vk::CommandBufferBeginInfo{vk::CommandBufferUsageFlagBits::eOneTimeSubmit});
    vk::ImageMemoryBarrier barrier{vk::AccessFlagBits::eNone, vk::AccessFlagBits::eTransferWrite,
        vk::ImageLayout::eUndefined, vk::ImageLayout::eTransferDstOptimal,
        VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED, *this->dummyImage,
        {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}};
    copyCmd.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer, {}, nullptr, nullptr, barrier);
    vk::BufferImageCopy copyRegion{0, 0, 0, {vk::ImageAspectFlagBits::eColor, 0, 0, 1}, {0, 0, 0}, {1, 1, 1}};
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
    this->dummySampler.emplace(*this->device,
        vk::SamplerCreateInfo{{}, vk::Filter::eLinear, vk::Filter::eLinear, vk::SamplerMipmapMode::eLinear,
            vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat, vk::SamplerAddressMode::eRepeat});

    // 描述符池：分配 2 个 CombinedImageSampler（图片管线 + 字体管线）
    vk::DescriptorPoolSize poolSize{vk::DescriptorType::eCombinedImageSampler, 2};
    this->descPool.emplace(*this->device,
        vk::DescriptorPoolCreateInfo{vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet, 2, 1, &poolSize});

    // 描述符集 0：图片管线
    {
        auto descSets = this->device->allocateDescriptorSets(
            vk::DescriptorSetAllocateInfo{*this->descPool, 1, &**this->descSetLayout});
        this->descSet.emplace(std::move(descSets.front()));
        vk::DescriptorImageInfo imageInfo{*this->dummySampler, *this->dummyImageView, vk::ImageLayout::eShaderReadOnlyOptimal};
        vk::WriteDescriptorSet writeDesc{**this->descSet, 0, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo, nullptr, nullptr};
        this->device->updateDescriptorSets(writeDesc, nullptr);
    }

    // 描述符集 1：字体管线
    {
        auto descSets = this->device->allocateDescriptorSets(
            vk::DescriptorSetAllocateInfo{*this->descPool, 1, &**this->descSetLayout});
        this->fontDescSet.emplace(std::move(descSets.front()));
        vk::DescriptorImageInfo imageInfo{*this->dummySampler, *this->dummyImageView, vk::ImageLayout::eShaderReadOnlyOptimal};
        vk::WriteDescriptorSet writeDesc{**this->fontDescSet, 0, 0, 1, vk::DescriptorType::eCombinedImageSampler, &imageInfo, nullptr, nullptr};
        this->device->updateDescriptorSets(writeDesc, nullptr);
    }

    return *this;
}
}