namespace youklx {
    void Wvulkan::drawFrame() {
        if (framebufferResized) {
            // 窗口最小化时 w/h 为 0，跳过重建等待恢复
            if (pendingWidth == 0 || pendingHeight == 0) {
                return;
            }
            try {
                recreateSwapchain();
            } catch (const vk::OutOfDateKHRError&) {
                return; // surface 仍未就绪（最小化恢复中），保持标记下帧重试
            } catch (const vk::Error&) {
                return; // 其他 Vulkan 错误也跳过，避免崩溃
            }
        }

        // 在重建后提取原始 C 句柄（handle 可能因重建而更新）
        // acquireNextImage / present 可能返回 OutOfDate，Vulkan-Hpp 对此抛异常故用 C API
        VkDevice       vkd       = static_cast<VkDevice>(**device);
        VkFence        vkf       = static_cast<VkFence>(*syncObjects.inFlightFence);
        VkSemaphore    imgAvail  = static_cast<VkSemaphore>(*syncObjects.imageAvailableSemaphore);
        VkSemaphore    renderSem = static_cast<VkSemaphore>(*syncObjects.renderFinishedSemaphore);
        VkSwapchainKHR vkSwap    = static_cast<VkSwapchainKHR>(*swapchain.swapchain);
        VkQueue vkq;
        vkGetDeviceQueue(vkd, graphicsFamilyIndex, 0, &vkq);

        // --- 1. 等待上一帧 GPU 完成 ---
        if (device->waitForFences({*syncObjects.inFlightFence}, true,
                std::numeric_limits<uint64_t>::max()) != vk::Result::eSuccess) {
            throw std::runtime_error("等待帧围栏失败");
        }
        device->resetFences({*syncObjects.inFlightFence});

        // --- 2. 获取下一个交换链图像 ---
        uint32_t imageIndex;
        VkResult vkResult = vkAcquireNextImageKHR(vkd, vkSwap, UINT64_MAX,
            imgAvail, VK_NULL_HANDLE, &imageIndex);

        if (vkResult == VK_ERROR_OUT_OF_DATE_KHR) {
            framebufferResized = true;
            return;
        }
        if (vkResult != VK_SUCCESS && vkResult != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("获取交换链图像失败");
        }

        // --- 3. 提交命令缓冲 ---
        VkCommandBuffer cmdBuf = static_cast<VkCommandBuffer>(
            *commandBuffer.commandBuffers[imageIndex]);
        VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &imgAvail;
        submitInfo.pWaitDstStageMask = &waitStage;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &cmdBuf;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &renderSem;

        vkResult = vkQueueSubmit(vkq, 1, &submitInfo, vkf);
        if (vkResult != VK_SUCCESS) {
            throw std::runtime_error("提交命令缓冲失败");
        }

        // --- 4. 呈现 ---
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &renderSem;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &vkSwap;
        presentInfo.pImageIndices = &imageIndex;

        vkResult = vkQueuePresentKHR(vkq, &presentInfo);
        if (vkResult == VK_SUBOPTIMAL_KHR || vkResult == VK_ERROR_OUT_OF_DATE_KHR) {
            framebufferResized = true;
        } else if (vkResult != VK_SUCCESS) {
            throw std::runtime_error("呈现图像失败");
        }
    }
}
