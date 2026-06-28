namespace youklx {
    Vulkan& Vulkan::createFramebuffers() {
        // 为每张交换链图像视图创建对应的帧缓冲
        for (const auto& imageView : swapChainImageViews) {
            swapChainFramebuffers.emplace_back(*device,
                vk::FramebufferCreateInfo{{}, *renderPass, 1, &*imageView,
                    swapChainExtent.width, swapChainExtent.height, 1});
        }
        return *this;
    }
}