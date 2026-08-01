vk::raii::PhysicalDevice* physicalDevice{nullptr};
vk::raii::Device* device{nullptr};
vk::raii::SurfaceKHR* surface{nullptr};
int w{0};
int h{0};
vk::Format format{vk::Format::eUndefined};
vk::raii::SwapchainKHR swapchain{nullptr};
vk::Extent2D extent{0, 0};
std::vector<vk::raii::ImageView> imageViews;