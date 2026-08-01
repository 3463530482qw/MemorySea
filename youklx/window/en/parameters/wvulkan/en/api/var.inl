SDL_Window* id{nullptr};
Swapchain swapchain;
Renderpass renderpass;
Framebuffer framebuffer;
CommandPool commandPool;
SyncObjects syncObjects;
CommandBuffer commandBuffer;
bool framebufferResized{false}; // 窗口尺寸变化，需重建交换链
uint32_t pendingWidth{0};       // 待重建的交换链宽度（= 窗口 w）
uint32_t pendingHeight{0};      // 待重建的交换链高度（= 窗口 h）