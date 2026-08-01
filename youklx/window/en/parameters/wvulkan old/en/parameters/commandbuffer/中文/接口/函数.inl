void 创建命令缓冲(const vk::raii::Device& 设备, const vk::raii::CommandPool& 命令池, uint32_t 数量) { return createCommandBuffers(设备, 命令池, 数量); }
void 录制命令缓冲(const vk::raii::RenderPass& 渲染通道, const std::vector<vk::raii::Framebuffer>& 帧缓冲列表, vk::Extent2D 范围) { return recordCommandBuffers(渲染通道, 帧缓冲列表, 范围); }
