namespace youklx {
    Vulkan& Vulkan::createCommandPool() {
        // 创建命令池（允许单独重置命令缓冲，适合逐帧重录）
        commandPool.emplace(*device,
            vk::CommandPoolCreateInfo{
                vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
                graphicsFamilyIndex});
        return *this;
    }
}