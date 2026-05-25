namespace youklx {
    Vulkan& Vulkan::createSyncObjects() {
        vk::SemaphoreCreateInfo semaphoreInfo{};
        vk::FenceCreateInfo fenceInfo{vk::FenceCreateFlagBits::eSignaled};

        // imageAvailableSemaphores 和 inFlightFences 的数量与 MAX_FRAMES_IN_FLIGHT 对齐
        for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            this->imageAvailableSemaphores.emplace_back(*this->device, semaphoreInfo);
            this->inFlightFences.emplace_back(*this->device, fenceInfo);
        }

        // renderFinishedSemaphores 的数量与交换链图像数量对齐
        for (size_t i = 0; i < this->swapChainImages.size(); i++) {
            this->renderFinishedSemaphores.emplace_back(*this->device, semaphoreInfo);
        }

        return *this;
    }
}