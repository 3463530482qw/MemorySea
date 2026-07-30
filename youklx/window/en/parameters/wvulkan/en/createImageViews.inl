namespace youklx {
    void Wvulkan::createImageViews(const vk::raii::Device& device) {
        swapchain.createImageViews(device);
    }
}
