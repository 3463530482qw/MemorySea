namespace youklx {
    void CommandBuffer::recordCommandBuffers() {
        // vpW/vpH 为 0 时用交换链全尺寸（兼容未设置视口的情况）
        vk::Extent2D vpExtent{vpW, vpH};
        if (vpExtent.width == 0 && vpExtent.height == 0) {
            vpExtent = *extent;
        }
        vk::Offset2D vpOffset{vpX, vpY};

        // 清屏颜色：深灰背景
        vk::ClearValue clearValue;
        clearValue.setColor(vk::ClearColorValue{std::array{0.1f, 0.1f, 0.1f, 1.0f}});

        // 视口：按设置的偏移和渲染区域配置
        vk::Viewport viewport;
        viewport.setX(static_cast<float>(vpOffset.x));
        viewport.setY(static_cast<float>(vpOffset.y));
        viewport.setWidth(static_cast<float>(vpExtent.width));
        viewport.setHeight(static_cast<float>(vpExtent.height));
        viewport.setMinDepth(0.0f);
        viewport.setMaxDepth(1.0f);

        // 裁剪区域与视口匹配
        vk::Rect2D scissor{vpOffset, vpExtent};
        // 渲染区域与裁剪一致（清除仅作用于该区域）
        vk::Rect2D renderArea{vpOffset, vpExtent};

        for (size_t i = 0; i < commandBuffers.size(); i++) {
            vk::CommandBufferBeginInfo beginInfo;
            beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eSimultaneousUse);

            commandBuffers[i].begin(beginInfo);

            vk::RenderPassBeginInfo rpInfo;
            rpInfo.setRenderPass(**renderPass);
            rpInfo.setFramebuffer(*(*framebuffers)[i]);
            rpInfo.setRenderArea(renderArea);
            rpInfo.setClearValueCount(1);
            rpInfo.setPClearValues(&clearValue);

            commandBuffers[i].beginRenderPass(rpInfo, vk::SubpassContents::eInline);
            commandBuffers[i].setViewport(0, viewport);
            commandBuffers[i].setScissor(0, scissor);
            commandBuffers[i].endRenderPass();
            commandBuffers[i].end();
        }
    }
}