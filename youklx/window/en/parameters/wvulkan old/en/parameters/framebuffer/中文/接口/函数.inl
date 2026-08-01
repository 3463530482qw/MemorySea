void 创建帧缓冲(const vk::raii::Device& 设备, const vk::raii::RenderPass& 渲染通道, const std::vector<vk::raii::ImageView>& 图像视图, vk::Extent2D 范围) { return createFramebuffers(设备, 渲染通道, 图像视图, 范围); }
