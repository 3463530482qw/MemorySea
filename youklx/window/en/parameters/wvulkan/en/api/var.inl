std::optional<vk::raii::SurfaceKHR> surface;
uint32_t graphicsFamilyIndex{0};
bool framebufferResized{false};      // 窗口尺寸变化，需重建交换链
uint32_t pendingWidth{0};            // 待重建的交换链宽度（= 窗口 w）
uint32_t pendingHeight{0};           // 待重建的交换链高度（= 窗口 h）
int32_t vpX{0};                      // viewport 偏移 x（= dix）
int32_t vpY{0};                      // viewport 偏移 y（= diy）
uint32_t vpW{0};                     // viewport 宽度（= rex）
uint32_t vpH{0};                     // viewport 高度（= rey）
Swapchain swapchain;
RenderPass renderpass;
Framebuffer framebuffer;
CommandPool commandPool;
SyncObjects syncObjects;
CommandBuffer commandBuffer;