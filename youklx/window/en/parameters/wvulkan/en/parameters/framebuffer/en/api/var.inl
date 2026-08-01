vk::raii::Device* device{nullptr};
vk::raii::RenderPass* renderPass{nullptr};
std::vector<vk::raii::ImageView>* imageViews{nullptr};
vk::Extent2D* extent{nullptr};
std::vector<vk::raii::Framebuffer> framebuffers;