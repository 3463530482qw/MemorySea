namespace youklx {
    Vulkan& Vulkan::createRenderPass() {
        bool useMsaa = msaaSamples != vk::SampleCountFlagBits::e1;

        // MSAA 颜色附件（多样本渲染目标）
        vk::AttachmentDescription msaaAttachment{};
        vk::AttachmentReference msaaRef{};
        if (useMsaa) {
            msaaAttachment = {{}, swapChainImageFormat, msaaSamples,
                vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eDontCare,
                vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare,
                vk::ImageLayout::eUndefined, vk::ImageLayout::eColorAttachmentOptimal};
            msaaRef = {1, vk::ImageLayout::eColorAttachmentOptimal};
        }

        // 颜色附件（无 MSAA 时直接呈现，有 MSAA 时作为 resolve 目标）
        vk::AttachmentDescription colorAttachment{
            {}, swapChainImageFormat,
            vk::SampleCountFlagBits::e1,
            vk::AttachmentLoadOp::eClear, vk::AttachmentStoreOp::eStore,
            vk::AttachmentLoadOp::eDontCare, vk::AttachmentStoreOp::eDontCare,
            useMsaa ? vk::ImageLayout::eUndefined : vk::ImageLayout::eUndefined,
            vk::ImageLayout::ePresentSrcKHR};

        // 颜色附件引用（无 MSAA 时索引 0，有 MSAA 时 resolve）
        vk::AttachmentReference colorRef{0, vk::ImageLayout::eColorAttachmentOptimal};

        vk::SubpassDescription subpass{{}, vk::PipelineBindPoint::eGraphics,
            0, nullptr,
            useMsaa ? 1u : 1u,
            useMsaa ? &msaaRef : &colorRef,
            useMsaa ? &colorRef : nullptr,   // resolve 附件
            nullptr, 0, nullptr};

        // 附件列表
        std::vector<vk::AttachmentDescription> attachments{colorAttachment};
        if (useMsaa) attachments.push_back(msaaAttachment);

        vk::SubpassDependency dependency{
            VK_SUBPASS_EXTERNAL, 0,
            vk::PipelineStageFlagBits::eColorAttachmentOutput,
            vk::PipelineStageFlagBits::eColorAttachmentOutput,
            {}, vk::AccessFlagBits::eColorAttachmentWrite, {}};

        renderPass.emplace(*device,
            vk::RenderPassCreateInfo{{},
                static_cast<uint32_t>(attachments.size()), attachments.data(),
                1, &subpass, 1, &dependency});
        return *this;
    }
}