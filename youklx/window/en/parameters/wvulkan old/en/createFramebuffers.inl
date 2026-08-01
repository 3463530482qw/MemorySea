namespace youklx {
    void Wvulkan::createFramebuffers(const vk::raii::Device& device) {
        // 渲染通道、图像视图、范围全部复用已有成员
        framebuffer.createFramebuffers(device, renderpass.renderPass, swapchain.imageViews, swapchain.extent);
    }
}
