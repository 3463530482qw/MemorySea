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
        // 字体贴图在 Font 类内,首次绘制时惰性初始化,此处只建管线
        fontrender.init(vulkan.physicalDevice, vulkan.device, renderpass.renderPass, swapchain.format, swapchain.extent, graphicsFamilyIndex);
        framebufferResized = false; // 初始化完毕，清除窗口创建时可能残留的标记
    }
}