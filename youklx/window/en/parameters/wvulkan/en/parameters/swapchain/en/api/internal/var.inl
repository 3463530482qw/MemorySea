vk::raii::SwapchainKHR swapchain{nullptr};
vk::Format format{vk::Format::eUndefined};
vk::Extent2D extent{0, 0};
std::vector<vk::Image> images;
std::vector<vk::raii::ImageView> imageViews;