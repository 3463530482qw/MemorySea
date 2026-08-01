namespace youklx {
    void Wvulkan::recordCommandBuffers() {
        commandBuffer.recordCommandBuffers(
            renderpass.renderPass,
            framebuffer.framebuffers,
            swapchain.extent,                       // 帧缓冲尺寸 = 交换链全尺寸
            vk::Offset2D{vpX, vpY},                 // viewport 偏移 = dix, diy
            vk::Extent2D{vpW, vpH}                  // viewport 尺寸 = rex, rey（0 时自动用全尺寸）
        );
    }
}
