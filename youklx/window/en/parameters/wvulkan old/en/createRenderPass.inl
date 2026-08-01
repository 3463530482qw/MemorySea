namespace youklx {
    void Wvulkan::createRenderPass(const vk::raii::Device& device) {
        // 渲染通道颜色格式直接复用交换链格式
        renderpass.createRenderPass(device, swapchain.format);
    }
}
