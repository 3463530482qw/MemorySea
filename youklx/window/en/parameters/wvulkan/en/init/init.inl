namespace youklx {
    void Wvulkan::init(Vulkan& vulkan) {
        #include "method/inlinevar.inl"
        #include "method/createsurface.inl"
        #include "method/findgraphicsqueuefamily.inl"
        vulkan.createLogicalDevice(graphicsFamilyIndex);
        swapchain.createSwapchain();
        swapchain.createImageViews();
        renderpass.createRenderPass();
        framebuffer.createFramebuffers();
        commandPool.createCommandPool();
        syncObjects.createSyncObjects();
        commandBuffer.createCommandBuffers();
        commandBuffer.recordCommandBuffers();
        framebufferResized = false; // 初始化完毕，清除窗口创建时可能残留的标记
    }
}