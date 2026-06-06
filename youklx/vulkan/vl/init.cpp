namespace youklx {
    Vulkan& Vulkan::init(Window& window) {
        this->createInstance();
        this->pickPhysicalDevice();
        this->createSurface(window.id);
        this->findGraphicsQueueFamily();
        this->createDevice();
        this->createSwapChain();
        this->createRenderPass();
        this->createFramebuffers();
        this->createCommandPool();
        this->createCommandBuffers();
        this->createSyncObjects();
        this->createPipeline();
        return *this;
    }
}
