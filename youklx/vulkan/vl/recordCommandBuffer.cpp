namespace youklx {
    Vulkan& Vulkan::recordCommandBuffer(uint32_t imageIndex, Draw& draw) {
        this->commandBuffers[this->currentFrame].reset();
        vk::CommandBufferBeginInfo beginInfo{};
        this->commandBuffers[this->currentFrame].begin(beginInfo);
        vk::ClearValue clearColor{vk::ClearColorValue{std::array<float,4>{0.0f,0.0f,0.0f,1.0f}}};
        vk::RenderPassBeginInfo renderPassInfo{*this->renderPass,*this->swapChainFramebuffers[imageIndex],vk::Rect2D{{0,0},this->swapChainExtent},1,&clearColor};
        this->commandBuffers[this->currentFrame].beginRenderPass(renderPassInfo, vk::SubpassContents::eInline);

        uint32_t chainW = this->swapChainExtent.width;
        uint32_t chainH = this->swapChainExtent.height;
        uint32_t logW = static_cast<uint32_t>(this->stsizew);
        uint32_t logH = static_cast<uint32_t>(this->stsizeh);
        float targetRatio = static_cast<float>(logW)/static_cast<float>(logH);
        float chainRatio = static_cast<float>(chainW)/static_cast<float>(chainH);
        uint32_t vpW = chainW, vpH = chainH;
        if (chainRatio > targetRatio) { vpH = chainH; vpW = static_cast<uint32_t>(chainH * targetRatio); }
        else { vpW = chainW; vpH = static_cast<uint32_t>(chainW / targetRatio); }
        int32_t offsetX = static_cast<int32_t>((chainW - vpW)/2);
        int32_t offsetY = static_cast<int32_t>((chainH - vpH)/2);
        vk::Viewport viewport{static_cast<float>(offsetX),static_cast<float>(offsetY),static_cast<float>(vpW),static_cast<float>(vpH),0.0f,1.0f};
        this->commandBuffers[this->currentFrame].setViewport(0, viewport);
        vk::Rect2D scissor{{offsetX,offsetY},{vpW,vpH}};
        this->commandBuffers[this->currentFrame].setScissor(0, scissor);
        float mvp[16] = {2.0f/logW,0,0,0, 0,2.0f/logH,0,0, 0,0,1,0, -1,-1,0,1};
        this->commandBuffers[this->currentFrame].pushConstants<float>(*this->pipelineLayout, vk::ShaderStageFlagBits::eVertex, 0, {mvp[0],mvp[1],mvp[2],mvp[3],mvp[4],mvp[5],mvp[6],mvp[7],mvp[8],mvp[9],mvp[10],mvp[11],mvp[12],mvp[13],mvp[14],mvp[15]});

        // 遍历绘制命令，按类型绑定不同管线
        for (int i = 0; i < draw.cptr; ++i) {
            // 获取当前命令的起始顶点索引（由 vupdate 填充）
            uint32_t firstVertex = (i < static_cast<int>(draw.vertexptr.size()))
                ? static_cast<uint32_t>(draw.vertexptr[i]) : 0u;
            // 计算实际顶点数：如果不是最后一条命令，取差值；否则取剩余全部
            uint32_t vertexCount = 0;
            if (i < static_cast<int>(draw.vertexptr.size())) {
                uint32_t nextOffset = (i + 1 < draw.cptr && (i + 1) < static_cast<int>(draw.vertexptr.size()))
                    ? static_cast<uint32_t>(draw.vertexptr[i + 1])
                    : static_cast<uint32_t>(draw.vertex.size() / 8);
                if (nextOffset > firstVertex) {
                    vertexCount = nextOffset - firstVertex;
                }
            }
            if (vertexCount == 0) continue; // 跳过退化命令

            std::visit(overloaded{
                    [this, firstVertex, vertexCount](Linecmd&) {
                        this->commandBuffers[this->currentFrame].bindPipeline(vk::PipelineBindPoint::eGraphics, *this->graphicsPipeline);
                        if (this->descSet) {
                            this->commandBuffers[this->currentFrame].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *this->pipelineLayout, 0, {**this->descSet}, nullptr);
                        }
                        vk::DeviceSize vbOffsets{0};
                        this->commandBuffers[this->currentFrame].bindVertexBuffers(0, {**this->vertexBuffer}, vbOffsets);
                        this->commandBuffers[this->currentFrame].draw(vertexCount, 1, firstVertex, 0);
                    },
                [this, firstVertex, vertexCount](Imagecmd&) {
                    this->commandBuffers[this->currentFrame].bindPipeline(vk::PipelineBindPoint::eGraphics, *this->graphicsPipelineImage);
                    if (this->descSet) {
                        this->commandBuffers[this->currentFrame].bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *this->pipelineLayout, 0, {**this->descSet}, nullptr);
                    }
                    vk::DeviceSize vbOffsets{0};
                    this->commandBuffers[this->currentFrame].bindVertexBuffers(0, {**this->vertexBuffer}, vbOffsets);
                    this->commandBuffers[this->currentFrame].draw(vertexCount, 1, firstVertex, 0);
                },
            }, draw.commands[i]);
        }

        this->commandBuffers[this->currentFrame].endRenderPass();
        this->commandBuffers[this->currentFrame].end();
        return *this;
    }
}