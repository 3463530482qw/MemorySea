namespace youklx {
    Vulkan& Vulkan::createCommandPool() {
        // 命令池创建信息
        vk::CommandPoolCreateInfo createInfo{
            vk::CommandPoolCreateFlagBits::eResetCommandBuffer, // 允许单独重置命令缓冲
            this->graphicsFamilyIndex                     // 队列族索引
        };

        // 创建命令池
        this->commandPool.emplace(*this->device, createInfo);

        return *this;
    }
}