namespace youklx {
    void CommandBuffer::createCommandBuffers() {
        // 从命令池中为每张交换链图像分配一个主命令缓冲
        vk::CommandBufferAllocateInfo allocInfo;
        allocInfo.setCommandPool(**commandPool);
        allocInfo.setLevel(vk::CommandBufferLevel::ePrimary);
        allocInfo.setCommandBufferCount(static_cast<uint32_t>(imageViews->size()));

        commandBuffers = vk::raii::CommandBuffers(*device, allocInfo);
    }
}