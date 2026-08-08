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
        // init 时字体可能还没加载(null),首次 run() 时由窗口绑定
        fontrender.init(vulkan.physicalDevice, vulkan.device, renderpass.renderPass, swapchain.format, swapchain.extent, nullptr, graphicsFamilyIndex);
        framebufferResized = false; // 初始化完毕，清除窗口创建时可能残留的标记
    }
}