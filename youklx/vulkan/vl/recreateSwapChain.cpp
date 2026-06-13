namespace youklx {
    Vulkan& Vulkan::recreateSwapChain() {
        // 如果窗口最小化（尺寸为0），直接返回，等下一帧重试
        auto caps = this->physicalDevice->getSurfaceCapabilitiesKHR(*this->surface);
        if (caps.currentExtent.width == 0 || caps.currentExtent.height == 0) {
            return *this;
        }

        // 等待所有在途 GPU 工作完成再清理资源，超时 2 秒
        if (!this->inFlightFences.empty()) {
            std::vector<vk::Fence> fences;
            fences.reserve(this->inFlightFences.size());
            for (auto& f : this->inFlightFences) {
                fences.push_back(*f);
            }
            auto idleResult = (*this->device).waitForFences(
                fences, VK_TRUE, 2'000'000'000);
            if (idleResult == vk::Result::eTimeout) {
                std::cerr << "Vulkan: recreateSwapChain 等待 GPU 空闲超时，强制重建" << std::endl;
            }
        }

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