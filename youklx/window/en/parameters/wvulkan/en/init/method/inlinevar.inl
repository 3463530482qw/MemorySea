instance = &vulkan.instance;
device = &vulkan.device;
swapchain.physicalDevice = &vulkan.physicalDevice;
swapchain.device = &vulkan.device;
swapchain.surface = &surface;
renderpass.device = &vulkan.device;
renderpass.format = &swapchain.format;
framebuffer.device = &vulkan.device;
framebuffer.renderPass = &renderpass.renderPass;
framebuffer.imageViews = &swapchain.imageViews;
framebuffer.extent = &swapchain.extent;
commandPool.device = &vulkan.device;
commandPool.queueFamilyIndex = &graphicsFamilyIndex;
syncObjects.device = &vulkan.device;
commandBuffer.device = &vulkan.device;
commandBuffer.commandPool = &commandPool.commandPool;
commandBuffer.renderPass = &renderpass.renderPass;
commandBuffer.framebuffers = &framebuffer.framebuffers;
commandBuffer.imageViews = &swapchain.imageViews;
commandBuffer.extent = &swapchain.extent;
commandBuffer.drawCallback = [this](vk::raii::CommandBuffer& cb) {
    // 直接用 wvulkan 的 drawVertices(运行时由窗口注入,不能用 init 时的快照)
    // 投影用逻辑画布尺寸(逻辑坐标→NDC,viewport 负责映射到物理像素)
    fontrender.camera = camera;   // 相机同步(窗口每帧注入)
    if (drawVertices) fontrender.draw(cb, *drawVertices, static_cast<float>(*logicW), static_cast<float>(*logicH));
};