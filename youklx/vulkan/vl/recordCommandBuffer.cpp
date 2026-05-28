namespace youklx {
    Vulkan& Vulkan::recordCommandBuffer(uint32_t imageIndex) {
        this->commandBuffers[this->currentFrame].reset();

        vk::CommandBufferBeginInfo beginInfo{};
        this->commandBuffers[this->currentFrame].begin(beginInfo);

        vk::ClearValue clearColor{
            vk::ClearColorValue{std::array<float, 4>{0.1f, 0.1f, 0.15f, 1.0f}}
        };

        vk::RenderPassBeginInfo renderPassInfo{
            *this->renderPass,
            *this->swapChainFramebuffers[imageIndex],
            vk::Rect2D{{0, 0}, this->swapChainExtent},
            1,
            &clearColor
        };
        this->commandBuffers[this->currentFrame].beginRenderPass(
            renderPassInfo, vk::SubpassContents::eInline
        );

        // 绑定图形管线
        this->commandBuffers[this->currentFrame].bindPipeline(
            vk::PipelineBindPoint::eGraphics, *this->graphicsPipeline
        );

        // 交换链实际尺寸
        uint32_t chainW = this->swapChainExtent.width;
        uint32_t chainH = this->swapChainExtent.height;

        // 逻辑画布尺寸
        uint32_t logW = static_cast<uint32_t>(this->stsizew);
        uint32_t logH = static_cast<uint32_t>(this->stsizeh);

        // 目标比例
        float targetRatio = static_cast<float>(logW) / static_cast<float>(logH);
        float chainRatio = static_cast<float>(chainW) / static_cast<float>(chainH);

        // 在交换链内计算最大等比例矩形
        uint32_t vpW = chainW;
        uint32_t vpH = chainH;
        if (chainRatio > targetRatio) {
            vpH = chainH;
            vpW = static_cast<uint32_t>(chainH * targetRatio);
        } else {
            vpW = chainW;
            vpH = static_cast<uint32_t>(chainW / targetRatio);
        }

        // 居中偏移
        int32_t offsetX = static_cast<int32_t>((chainW - vpW) / 2);
        int32_t offsetY = static_cast<int32_t>((chainH - vpH) / 2);

        // 设置居中视口
        vk::Viewport viewport{
            static_cast<float>(offsetX), static_cast<float>(offsetY),
            static_cast<float>(vpW), static_cast<float>(vpH),
            0.0f, 1.0f
        };
        this->commandBuffers[this->currentFrame].setViewport(0, viewport);

        // 设置居中剪刀
        vk::Rect2D scissor{
            {offsetX, offsetY},
            {vpW, vpH}
        };
        this->commandBuffers[this->currentFrame].setScissor(0, scissor);

        // 构建 MVP 矩阵：逻辑画布归一化 -> NDC
        // 将逻辑坐标 [0, logW] x [0, logH] 映射到 NDC [-1, 1]
        float mvp[16] = {
            2.0f / logW, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f / logH, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 1.0f
        };

        // 通过 push constant 传入 MVP 矩阵
        this->commandBuffers[this->currentFrame].pushConstants<float>(
            *this->pipelineLayout,
            vk::ShaderStageFlagBits::eVertex,
            0,
            {mvp[0], mvp[1], mvp[2], mvp[3],
             mvp[4], mvp[5], mvp[6], mvp[7],
             mvp[8], mvp[9], mvp[10], mvp[11],
             mvp[12], mvp[13], mvp[14], mvp[15]}
        );

        // 绑定顶点缓冲并绘制
        if (this->vertexBuffer && this->vertexCount > 0) {
            vk::DeviceSize offsets{0};
            this->commandBuffers[this->currentFrame].bindVertexBuffers(
                0, {**this->vertexBuffer}, offsets
            );
            this->commandBuffers[this->currentFrame].draw(
                this->vertexCount, 1, 0, 0
            );
        }

        this->commandBuffers[this->currentFrame].endRenderPass();
        this->commandBuffers[this->currentFrame].end();

        return *this;
    }
}