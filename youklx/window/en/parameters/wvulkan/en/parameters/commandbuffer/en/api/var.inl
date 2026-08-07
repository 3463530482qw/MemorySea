vk::raii::Device* device{nullptr};
vk::raii::CommandPool* commandPool{nullptr};
vk::raii::RenderPass* renderPass{nullptr};
std::vector<vk::raii::Framebuffer>* framebuffers{nullptr};
std::vector<vk::raii::ImageView>* imageViews{nullptr};
vk::Extent2D* extent{nullptr};
std::function<void(vk::raii::CommandBuffer&)> drawCallback;  // 绘制回调(由 wvulkan 注入)
int32_t vpX{0};
int32_t vpY{0};
uint32_t vpW{0};
uint32_t vpH{0};
std::vector<vk::raii::CommandBuffer> commandBuffers;
