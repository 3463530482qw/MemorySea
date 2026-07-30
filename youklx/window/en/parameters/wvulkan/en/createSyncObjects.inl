namespace youklx {
    void Wvulkan::createSyncObjects(const vk::raii::Device& device) {
        syncObjects.createSyncObjects(device);
    }
}
