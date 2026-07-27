namespace youklx {
    Vulkan& Vulkan::createCommandBuffers() {
        // 分配 MAX_FRAMES_IN_FLIGHT 个主命令缓冲（每帧一个，避免飞行中冲突）
        commandBuffers = std::move(
            device->allocateCommandBuffers(
                vk::CommandBufferAllocateInfo{*commandPool,
                    vk::CommandBufferLevel::ePrimary, MAX_FRAMES_IN_FLIGHT}));
        return *this;
    }
}