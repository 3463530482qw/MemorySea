namespace youklx {
    void Wvulkan::recordCommandBuffers() {
        commandBuffer.recordCommandBuffers(
            renderpass.renderPass,
            framebuffer.framebuffers,
            swapchain.extent
        );
    }
}
