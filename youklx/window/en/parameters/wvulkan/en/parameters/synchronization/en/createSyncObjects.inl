namespace youklx {
    void SyncObjects::createSyncObjects(const vk::raii::Device& device) {
        // 信号量和围栏创建时均为 unsignaled 状态
        vk::SemaphoreCreateInfo semaphoreInfo;
        vk::FenceCreateInfo fenceInfo;
        // 围栏初始为 signaled 状态，避免首帧等待时死锁
        fenceInfo.setFlags(vk::FenceCreateFlagBits::eSignaled);

        imageAvailableSemaphore = vk::raii::Semaphore(device, semaphoreInfo);
        renderFinishedSemaphore = vk::raii::Semaphore(device, semaphoreInfo);
        inFlightFence            = vk::raii::Fence(device, fenceInfo);
    }
}
