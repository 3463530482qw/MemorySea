namespace youklx {
    void Wvulkan::drawFrame(const vk::raii::Device& device) {
        // 提取原始 C 句柄（跨模块安全：整数/指针，无 dispatch table 依赖）
        VkDevice vkd = static_cast<VkDevice>(*device);
        VkFence vkf = static_cast<VkFence>(*syncObjects.inFlightFence);
        VkSemaphore imageAvail = static_cast<VkSemaphore>(*syncObjects.imageAvailableSemaphore);
        VkSemaphore renderDone = static_cast<VkSemaphore>(*syncObjects.renderFinishedSemaphore);
        VkSwapchainKHR vkSwap = static_cast<VkSwapchainKHR>(*swapchain.swapchain);
        VkQueue vkq;
        vkGetDeviceQueue(vkd, graphicsFamilyIndex, 0, &vkq);

        // 1. 等待上一帧 GPU 完成
        VkResult result = vkWaitForFences(vkd, 1, &vkf, VK_TRUE, UINT64_MAX);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("等待帧围栏失败");
        }
        vkResetFences(vkd, 1, &vkf);

        // 2. 获取下一个可用的交换链图像索引
        uint32_t imageIndex;
        result = vkAcquireNextImageKHR(vkd, vkSwap, UINT64_MAX,
            imageAvail, VK_NULL_HANDLE, &imageIndex);
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("获取交换链图像失败");
        }

        // 3. 提交命令缓冲
        VkCommandBuffer cmdBuf = static_cast<VkCommandBuffer>(
            *commandBuffer.commandBuffers[imageIndex]);
        VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = &imageAvail;
        submitInfo.pWaitDstStageMask = &waitStage;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &cmdBuf;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = &renderDone;

        result = vkQueueSubmit(vkq, 1, &submitInfo, vkf);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("提交命令缓冲失败");
        }

        // 4. 呈现
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = &renderDone;
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = &vkSwap;
        presentInfo.pImageIndices = &imageIndex;

        result = vkQueuePresentKHR(vkq, &presentInfo);
        if (result != VK_SUCCESS &&
            result != VK_SUBOPTIMAL_KHR &&
            result != VK_ERROR_OUT_OF_DATE_KHR) {
            throw std::runtime_error("呈现图像失败");
        }
    }
}
