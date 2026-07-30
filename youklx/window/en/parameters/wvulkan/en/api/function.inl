void createSurface(SDL_Window* window, const vk::raii::Instance& instance);
void findGraphicsQueueFamily(const vk::raii::PhysicalDevice& physicalDevice);
void createSwapchain(const vk::raii::PhysicalDevice& physicalDevice, const vk::raii::Device& device, uint32_t width, uint32_t height);
void createImageViews(const vk::raii::Device& device);
void createRenderPass(const vk::raii::Device& device);
void createFramebuffers(const vk::raii::Device& device);
void createCommandPool(const vk::raii::Device& device);
void createSyncObjects(const vk::raii::Device& device);