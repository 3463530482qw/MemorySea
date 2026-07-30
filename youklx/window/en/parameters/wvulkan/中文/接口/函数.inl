void 创建表面(SDL_Window* 窗口, const vk::raii::Instance& 实例) { return createSurface(窗口, 实例); }
void 查找图形队列族(const vk::raii::PhysicalDevice& 物理设备) { return findGraphicsQueueFamily(物理设备); }
void 创建交换链(const vk::raii::PhysicalDevice& 物理设备, const vk::raii::Device& 设备, uint32_t 宽度, uint32_t 高度) { return createSwapchain(物理设备, 设备, 宽度, 高度); }
void 创建图像视图(const vk::raii::Device& 设备) { return createImageViews(设备); }
void 创建渲染通道(const vk::raii::Device& 设备) { return createRenderPass(设备); }
void 创建帧缓冲(const vk::raii::Device& 设备) { return createFramebuffers(设备); }
void 创建命令池(const vk::raii::Device& 设备) { return createCommandPool(设备); }