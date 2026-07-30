namespace youklx {
    void Wvulkan::createSwapchain(
        const vk::raii::PhysicalDevice& physicalDevice,
        const vk::raii::Device& device,
        uint32_t width,
        uint32_t height
    ) {
        swapchain.createSwapchain(physicalDevice, device, *surface, width, height);
    }
}
