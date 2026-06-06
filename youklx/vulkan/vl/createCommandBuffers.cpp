namespace youklx {
    Vulkan& Vulkan::createCommandBuffers() {
        // 分配命令缓冲
        vk::CommandBufferAllocateInfo allocInfo{
            *commandPool, 
            vk::CommandBufferLevel::ePrimary, 
            MAX_FRAMES_IN_FLIGHT              
        };

        commandBuffers = std::move(
            (*device).allocateCommandBuffers(allocInfo)
        );

        return *this;
    }
}