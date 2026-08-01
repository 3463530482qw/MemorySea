namespace youklx {
    void CommandPool::createCommandPool() {
        // 命令池创建信息：绑定到图形队列族，允许单独重置命令缓冲
        vk::CommandPoolCreateInfo createInfo;
        createInfo.setQueueFamilyIndex(*queueFamilyIndex);
        createInfo.setFlags(vk::CommandPoolCreateFlagBits::eResetCommandBuffer);

        commandPool = vk::raii::CommandPool(*device, createInfo);
    }
}