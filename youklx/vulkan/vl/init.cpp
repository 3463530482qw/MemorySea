namespace youklx {
    Vulkan& Vulkan::msaa(int samples) {
        if (samples >= 4) msaaSamples = vk::SampleCountFlagBits::e4;
        else if (samples >= 2) msaaSamples = vk::SampleCountFlagBits::e2;
        else msaaSamples = vk::SampleCountFlagBits::e1;
        return *this;
    }
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
