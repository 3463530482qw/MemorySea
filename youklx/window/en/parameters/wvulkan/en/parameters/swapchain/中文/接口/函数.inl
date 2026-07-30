void 创建交换链(const vk::raii::PhysicalDevice& 物理设备, const vk::raii::Device& 设备, const vk::raii::SurfaceKHR& 表面, uint32_t 宽度, uint32_t 高度) { return createSwapchain(物理设备, 设备, 表面, 宽度, 高度); }
void 创建图像视图(const vk::raii::Device& 设备) { return createImageViews(设备); }
