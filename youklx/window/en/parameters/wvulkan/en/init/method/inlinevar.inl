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
    // 纯录制:上传与顶点拷贝已由 prepare 在录制外完成
    fontrender.draw(cb);
};