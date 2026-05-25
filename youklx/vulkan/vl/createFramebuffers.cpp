namespace youklx {
    Vulkan& Vulkan::createFramebuffers() {
        // 为每张交换链图像视图创建对应的帧缓冲
        for (const auto& imageView : this->swapChainImageViews) {
            vk::FramebufferCreateInfo createInfo{
                {},                                       // flags
                *this->renderPass,                        // 渲染通道
                1,                                        // 附件数量
                &*imageView,                              // 附件（图像视图）
                this->swapChainExtent.width,              // 宽度
                this->swapChainExtent.height,             // 高度
                1                                         // 层数
            };

            this->swapChainFramebuffers.emplace_back(*this->device, createInfo);
        }

        return *this;
    }
}