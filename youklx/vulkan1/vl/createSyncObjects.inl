namespace youklx {
    Vulkan& Vulkan::createSyncObjects() {
        // 信号量：GPU→GPU 同步；围栏：GPU→CPU 同步
        auto semInfo = vk::SemaphoreCreateInfo{};
        auto fenceInfo = vk::FenceCreateInfo{vk::FenceCreateFlagBits::eSignaled};

        // 图像可用 / 飞行中围栏：每帧一个（MAX_FRAMES_IN_FLIGHT 个）
        for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            imageAvailableSemaphores.emplace_back(*device, semInfo);
            inFlightFences.emplace_back(*device, fenceInfo);
        }
        // 渲染完成信号量：每张交换链图像一个（避免信号量重用冲突）
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            renderFinishedSemaphores.emplace_back(*device, semInfo);
        }
        return *this;
    }
}
