namespace youklx {
    void Wvulkan::drawFrame(const vk::raii::Device& device) {
        // 1. 等待上一帧 GPU 完成（围栏未触发时阻塞，触发后重置）
        device.waitForFences(
            {*syncObjects.inFlightFence},
            true,
            std::numeric_limits<uint64_t>::max()
        );
        device.resetFences({*syncObjects.inFlightFence});

        // 2. 获取下一个可用的交换链图像索引
        auto [result, imageIndex] = swapchain.swapchain.acquireNextImage(
            std::numeric_limits<uint64_t>::max(),
            *syncObjects.imageAvailableSemaphore
        );

        if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR) {
            throw std::runtime_error("获取交换链图像失败");
        }

        // 3. 提交：等待图像可用 → 执行命令缓冲 → 发出渲染完成信号
        vk::PipelineStageFlags waitStage{vk::PipelineStageFlagBits::eColorAttachmentOutput};

        vk::SubmitInfo submitInfo;
        submitInfo.setWaitSemaphoreCount(1);
        submitInfo.setPWaitSemaphores(&(*syncObjects.imageAvailableSemaphore));
        submitInfo.setPWaitDstStageMask(&waitStage);
        submitInfo.setCommandBufferCount(1);
        submitInfo.setPCommandBuffers(&(*commandBuffer.commandBuffers[imageIndex]));
        submitInfo.setSignalSemaphoreCount(1);
        submitInfo.setPSignalSemaphores(&(*syncObjects.renderFinishedSemaphore));

        // 需要手动获取 vk::Queue 进行提交（vk::raii::Queue 不中断析构链）
        auto queue = device.getQueue(graphicsFamilyIndex, 0);
        queue.submit({submitInfo}, *syncObjects.inFlightFence);

        // 4. 呈现：等待渲染完成 → 把图像交给交换链显示
        vk::PresentInfoKHR presentInfo;
        presentInfo.setWaitSemaphoreCount(1);
        presentInfo.setPWaitSemaphores(&(*syncObjects.renderFinishedSemaphore));
        presentInfo.setSwapchainCount(1);
        presentInfo.setPSwapchains(&(*swapchain.swapchain));
        presentInfo.setPImageIndices(&imageIndex);

        result = queue.presentKHR(presentInfo);
        if (result == vk::Result::eSuboptimalKHR || result == vk::Result::eErrorOutOfDateKHR) {
            // 窗口尺寸变化，后续可在此重建交换链
        } else if (result != vk::Result::eSuccess) {
            throw std::runtime_error("呈现图像失败");
        }
    }
}
