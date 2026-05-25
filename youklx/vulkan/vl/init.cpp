namespace youklx {
    Vulkan& Vulkan::init(Window& window) {
        std::cout << "1. createInstance 开始" << std::endl;
        this->createInstance();
        std::cout << "1. createInstance 结束" << std::endl;

        std::cout << "2. pickPhysicalDevice 开始" << std::endl;
        this->pickPhysicalDevice();
        std::cout << "2. pickPhysicalDevice 结束" << std::endl;

        std::cout << "3. createSurface 开始" << std::endl;
        this->createSurface(window.id);
        std::cout << "3. createSurface 结束" << std::endl;

        std::cout << "4. findGraphicsQueueFamily 开始" << std::endl;
        this->findGraphicsQueueFamily();
        std::cout << "4. findGraphicsQueueFamily 结束" << std::endl;

        std::cout << "5. createDevice 开始" << std::endl;
        this->createDevice();
        std::cout << "5. createDevice 结束" << std::endl;

        std::cout << "6. createSwapChain 开始" << std::endl;
        this->createSwapChain();
        std::cout << "6. createSwapChain 结束" << std::endl;

        std::cout << "7. createRenderPass 开始" << std::endl;
        this->createRenderPass();
        std::cout << "7. createRenderPass 结束" << std::endl;

        std::cout << "8. createFramebuffers 开始" << std::endl;
        this->createFramebuffers();
        std::cout << "8. createFramebuffers 结束" << std::endl;

        std::cout << "9. createCommandPool 开始" << std::endl;
        this->createCommandPool();
        std::cout << "9. createCommandPool 结束" << std::endl;

        std::cout << "10. createCommandBuffers 开始" << std::endl;
        this->createCommandBuffers();
        std::cout << "10. createCommandBuffers 结束" << std::endl;

        std::cout << "11. createSyncObjects 开始" << std::endl;
        this->createSyncObjects();
        std::cout << "11. createSyncObjects 结束" << std::endl;

        return *this;
    }
}