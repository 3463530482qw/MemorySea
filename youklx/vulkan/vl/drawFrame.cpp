namespace youklx {
    Vulkan& Vulkan::drawFrame() {
        // 等待上一帧完成
        (void) (*this->device).waitForFences(
            {*this->inFlightFences[this->currentFrame]}, VK_TRUE, UINT64_MAX);

        uint32_t imageIndex = 0;
        try {
            auto result = (*this->swapChain).acquireNextImage(
                UINT64_MAX,
                *this->imageAvailableSemaphores[this->currentFrame],
                nullptr
            );
            // result 是 ResultValue<uint32_t>，必须取 .value
            imageIndex = result.value;
        } catch (const vk::OutOfDateKHRError& e) {
            this->recreateSwapChain();
            return *this;
        } catch (const vk::SystemError& e) {
            this->recreateSwapChain();
            return *this;
        } catch (...) {
            this->recreateSwapChain();
            return *this;
        }

        // 重置围栏
        (*this->device).resetFences({*this->inFlightFences[this->currentFrame]});

        // 记录命令
        this->recordCommandBuffer(imageIndex);

        // 提交
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

        // 呈现
        vk::PresentInfoKHR presentInfo{
            1,
            &*this->renderFinishedSemaphores[imageIndex],
            1,
            &**this->swapChain,
            &imageIndex
        };
        try {
            (void) this->graphicsQueue->presentKHR(presentInfo);
        } catch (const vk::SystemError& e) {
            this->recreateSwapChain();
        }

        // 切换到下一帧
        this->currentFrame = (this->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
        return *this;
    }
}