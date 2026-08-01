namespace youklx {
    void Wvulkan::recreateSwapchain() {
        device->waitIdle();

        commandBuffer.commandBuffers.clear();
        framebuffer.framebuffers.clear();
        swapchain.imageViews.clear();
        swapchain.swapchain = nullptr;

        // 把待重建的窗口尺寸同步给交换链
        swapchain.w = static_cast<int>(pendingWidth);
        swapchain.h = static_cast<int>(pendingHeight);

        swapchain.createSwapchain();
        swapchain.createImageViews();
        framebuffer.createFramebuffers();
        commandBuffer.createCommandBuffers();
        commandBuffer.recordCommandBuffers();

        framebufferResized = false;
    }
}
