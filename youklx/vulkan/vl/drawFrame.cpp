namespace youklx {
    Vulkan& Vulkan::drawFrame(Draw& draw) {
        // 防御：swapChain/commandBuffers 可能在运行时被 recreate 清空，
        // 缺失时安全跳过本帧而非崩溃
        if (!this->swapChain || this->commandBuffers.empty()) {
            return *this;
        }

        (void) (*this->device).waitForFences(
            {*this->inFlightFences[this->currentFrame]}, VK_TRUE, UINT64_MAX);

        uint32_t imageIndex = 0;
        try {
            auto result = (*this->swapChain).acquireNextImage(
                UINT64_MAX,
                *this->imageAvailableSemaphores[this->currentFrame],
                nullptr
            );
            imageIndex = result.value;
        } catch (const vk::OutOfDateKHRError&) {
            this->recreateSwapChain();
            return *this;
        } catch (const vk::SystemError&) {
            this->recreateSwapChain();
            return *this;
        } catch (...) {
            this->recreateSwapChain();
            return *this;
        }

        // 防御：recreate 后资源可能仍为空（如窗口最小化期间）
        if (this->commandBuffers.empty() || imageIndex >= this->swapChainFramebuffers.size() ||
            imageIndex >= this->renderFinishedSemaphores.size()) {
            return *this;
        }

        (*this->device).resetFences({*this->inFlightFences[this->currentFrame]});

        this->recordCommandBuffer(imageIndex, draw);

        vk::PipelineStageFlags waitStages[] = {
            vk::PipelineStageFlagBits::eColorAttachmentOutput
        };
        vk::SubmitInfo submitInfo{
            1,
            &*this->imageAvailableSemaphores[this->currentFrame],
            waitStages,
            1,
            &*this->commandBuffers[this->currentFrame],
            1,
             &*this->renderFinishedSemaphores[imageIndex]
        };
        this->graphicsQueue->submit(submitInfo, *this->inFlightFences[this->currentFrame]);

        vk::PresentInfoKHR presentInfo{
            1,
            &*this->renderFinishedSemaphores[imageIndex],
            1,
            &**this->swapChain,
            &imageIndex
        };
        try {
            (void) this->graphicsQueue->presentKHR(presentInfo);
        } catch (const vk::SystemError&) {
            this->recreateSwapChain();
        }

        this->currentFrame = (this->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
        return *this;
    }
}
