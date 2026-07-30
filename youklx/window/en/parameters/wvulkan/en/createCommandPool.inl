namespace youklx {
    void Wvulkan::createCommandPool(const vk::raii::Device& device) {
        commandPool.createCommandPool(device, graphicsFamilyIndex);
    }
}
