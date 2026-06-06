namespace youklx {
    Vulkan& Vulkan::createSyncObjects() {
        vk::SemaphoreCreateInfo semaphoreInfo{};
        vk::FenceCreateInfo fenceInfo{vk::FenceCreateFlagBits::eSignaled};

        // imageAvailableSemaphores 和 inFlightFences 的数量与 MAX_FRAMES_IN_FLIGHT 对齐
        for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            imageAvailableSemaphores.emplace_back(*device, semaphoreInfo);
            inFlightFences.emplace_back(*device, fenceInfo);
        }

        // renderFinishedSemaphores 每张交换链图像一个，避免信号量重用冲突
        for (size_t i = 0; i < swapChainImages.size(); i++) {
            renderFinishedSemaphores.emplace_back(*device, semaphoreInfo);
        }

        return *this;
    }
}
