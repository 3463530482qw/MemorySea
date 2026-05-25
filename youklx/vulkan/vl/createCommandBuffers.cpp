namespace youklx {
    Vulkan& Vulkan::createCommandBuffers() {
        // 分配命令缓冲
        vk::CommandBufferAllocateInfo allocInfo{
            *this->commandPool,                           // 命令池
            vk::CommandBufferLevel::ePrimary,             // 主命令缓冲
            MAX_FRAMES_IN_FLIGHT                         // 分配数量
        };

        this->commandBuffers = std::move(
            (*this->device).allocateCommandBuffers(allocInfo)
        );

        return *this;
    }
}