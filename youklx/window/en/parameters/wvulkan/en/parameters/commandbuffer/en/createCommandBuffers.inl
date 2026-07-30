namespace youklx {
    void CommandBuffer::createCommandBuffers(
        const vk::raii::Device& device,
        const vk::raii::CommandPool& commandPool,
        uint32_t count
    ) {
        // 从命令池中分配 count 个主命令缓冲
        vk::CommandBufferAllocateInfo allocInfo;
        allocInfo.setCommandPool(*commandPool);
        allocInfo.setLevel(vk::CommandBufferLevel::ePrimary);
        allocInfo.setCommandBufferCount(count);

        commandBuffers = vk::raii::CommandBuffers(device, allocInfo);
    }

    void CommandBuffer::recordCommandBuffers(
        const vk::raii::RenderPass& renderPass,
        const std::vector<vk::raii::Framebuffer>& framebuffers,
        vk::Extent2D extent
    ) {
        // 清屏颜色：深灰背景
        vk::ClearValue clearValue;
        clearValue.setColor(vk::ClearColorValue{std::array{0.1f, 0.1f, 0.1f, 1.0f}});

        // 视口撑满整个交换链范围
        vk::Viewport viewport;
        viewport.setX(0.0f);
        viewport.setY(0.0f);
        viewport.setWidth(static_cast<float>(extent.width));
        viewport.setHeight(static_cast<float>(extent.height));
        viewport.setMinDepth(0.0f);
        viewport.setMaxDepth(1.0f);

        // 裁剪区域与视口相同
        vk::Rect2D scissor{{0, 0}, extent};

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            // 开始录制：一次性提交（单帧不重用）
            vk::CommandBufferBeginInfo beginInfo;
            beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

            commandBuffers[i].begin(beginInfo);

            // 开始渲染通道：传入对应帧缓冲和清屏值
            vk::RenderPassBeginInfo rpInfo;
            rpInfo.setRenderPass(*renderPass);
            rpInfo.setFramebuffer(*framebuffers[i]);
            rpInfo.setRenderArea(scissor);
            rpInfo.setClearValueCount(1);
            rpInfo.setPClearValues(&clearValue);

            commandBuffers[i].beginRenderPass(rpInfo, vk::SubpassContents::eInline);
            commandBuffers[i].setViewport(0, viewport);
            commandBuffers[i].setScissor(0, scissor);
            // 绘制指令在此处插入（管线就绪后）
            commandBuffers[i].endRenderPass();
            commandBuffers[i].end();
        }
    }
}
