vk::raii::Device* device{nullptr};
vk::raii::CommandPool* commandPool{nullptr};
vk::raii::RenderPass* renderPass{nullptr};
std::vector<vk::raii::Framebuffer>* framebuffers{nullptr};
std::vector<vk::raii::ImageView>* imageViews{nullptr};
vk::Extent2D* extent{nullptr};
int32_t vpX{0};                     // viewport 偏移 x（= dix）
int32_t vpY{0};                     // viewport 偏移 y（= diy）
uint32_t vpW{0};                    // viewport 宽度（= rex，为 0 时用交换链全尺寸）
uint32_t vpH{0};                    // viewport 高度（= rey）
std::vector<vk::raii::CommandBuffer> commandBuffers;