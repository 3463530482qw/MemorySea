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
            // 交换链更宽，以高度为基准
            vpH = chainH;
            vpW = static_cast<uint32_t>(chainH * targetRatio);
        } else {
            // 交换链更高或等比例，以宽度为基准
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

        this->commandBuffers[this->currentFrame].endRenderPass();
        this->commandBuffers[this->currentFrame].end();

        return *this;
    }
}