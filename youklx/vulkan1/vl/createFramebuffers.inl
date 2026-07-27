namespace youklx {
    Vulkan& Vulkan::createFramebuffers() {
        bool useMsaa = msaaSamples != vk::SampleCountFlagBits::e1;

        // MSAA 时预先创建多样本图像（每个交换链图像对应一个）
        if (useMsaa) {
            msaaImages.clear(); msaaMemories.clear(); msaaViews.clear();
            msaaImages.reserve(swapChainImageViews.size());
            msaaMemories.reserve(swapChainImageViews.size());
            msaaViews.reserve(swapChainImageViews.size());

            for (size_t i = 0; i < swapChainImageViews.size(); i++) {
                vk::ImageCreateInfo imgInfo{{}, vk::ImageType::e2D, swapChainImageFormat,
                    {swapChainExtent.width, swapChainExtent.height, 1}, 1, 1,
                    msaaSamples, vk::ImageTiling::eOptimal,
                    vk::ImageUsageFlagBits::eTransientAttachment | vk::ImageUsageFlagBits::eColorAttachment};
                msaaImages.emplace_back(*device, imgInfo);
                auto reqs = msaaImages.back().getMemoryRequirements();
                uint32_t memType = findMemoryType(reqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);
                msaaMemories.emplace_back(*device, vk::MemoryAllocateInfo{reqs.size, memType});
                msaaImages.back().bindMemory(*msaaMemories.back(), 0);
                msaaViews.emplace_back(*device,
                    vk::ImageViewCreateInfo{{}, *msaaImages.back(), vk::ImageViewType::e2D,
                        swapChainImageFormat, {}, {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}});
            }
        }

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            std::vector<vk::ImageView> attachments;
            attachments.push_back(*swapChainImageViews[i]);  // resolve / 普通颜色
            if (useMsaa) attachments.push_back(*msaaViews[i]); // MSAA 附件
            swapChainFramebuffers.emplace_back(*device,
                vk::FramebufferCreateInfo{{}, *renderPass,
                    static_cast<uint32_t>(attachments.size()), attachments.data(),
                    swapChainExtent.width, swapChainExtent.height, 1});
        }
        return *this;
    }
}