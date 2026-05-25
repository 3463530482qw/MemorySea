namespace youklx {
    Vulkan& Vulkan::recreateSwapChain() {
        // 如果窗口最小化（尺寸为0），直接返回，等下一帧重试
        auto caps = this->physicalDevice->getSurfaceCapabilitiesKHR(*this->surface);
        if (caps.currentExtent.width == 0 || caps.currentExtent.height == 0) {
            return *this;
        }

        (*this->device).waitIdle();   // 等设备空闲再清理

        // 销毁所有依赖交换链的资源
        this->swapChainFramebuffers.clear();
        this->swapChainImageViews.clear();
        this->commandBuffers.clear();
        this->imageAvailableSemaphores.clear();
        this->renderFinishedSemaphores.clear();
        this->inFlightFences.clear();
        this->swapChain.reset();

        // 重新创建交换链与相关资源
        this->createSwapChain()
            .createRenderPass()
            .createFramebuffers()
            .createCommandBuffers()
            .createSyncObjects();

        this->currentFrame = 0;   // 重置帧索引
        return *this;
    }
}