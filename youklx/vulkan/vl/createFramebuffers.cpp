namespace youklx {
    Vulkan& Vulkan::createFramebuffers() {
        // 为每张交换链图像视图创建对应的帧缓冲
        for (const auto& imageView : swapChainImageViews) {
            vk::FramebufferCreateInfo createInfo{
                {},                                       // flags
                *renderPass,                              // 渲染通道
                1,                                        // 附件数量
                &*imageView,                              // 附件（图像视图）
                swapChainExtent.width,                    // 宽度
                swapChainExtent.height,                   // 高度
                1                                         // 层数
            };

            swapChainFramebuffers.emplace_back(*device, createInfo);
        }

        return *this;
    }
}