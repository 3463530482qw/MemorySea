SDL_Window* id{nullptr};
Swapchain swapchain;
Renderpass renderpass;
Framebuffer framebuffer;
CommandPool commandPool;
SyncObjects syncObjects;
CommandBuffer commandBuffer;
FontRender fontrender;
std::vector<Vertex>* drawVertices{nullptr};  // 绘制顶点(由窗口注入)
int *logicW{nullptr}, *logicH{nullptr};          // 逻辑画布尺寸(由窗口注入,投影用)
Camera* camera{nullptr};                // 相机(由窗口注入,投影变换用)
bool framebufferResized{false}; // 窗口尺寸变化，需重建交换链
uint32_t pendingWidth{0};       // 待重建的交换链宽度（= 窗口 w）
uint32_t pendingHeight{0};      // 待重建的交换链高度（= 窗口 h）