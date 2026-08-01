namespace youklx {
    void RenderPass::createRenderPass(const vk::raii::Device& device, vk::Format colorFormat) {
        format = colorFormat;

        // 1. 颜色附件描述：交换链图像作为唯一渲染目标
        //    帧开始清屏、结束保存，最终布局切换为呈现源供交换链显示
        vk::AttachmentDescription colorAttachment;
        colorAttachment.setFormat(colorFormat);
        colorAttachment.setSamples(vk::SampleCountFlagBits::e1);
        colorAttachment.setLoadOp(vk::AttachmentLoadOp::eClear);
        colorAttachment.setStoreOp(vk::AttachmentStoreOp::eStore);
        colorAttachment.setStencilLoadOp(vk::AttachmentLoadOp::eDontCare);
        colorAttachment.setStencilStoreOp(vk::AttachmentStoreOp::eDontCare);
        colorAttachment.setInitialLayout(vk::ImageLayout::eUndefined);
        colorAttachment.setFinalLayout(vk::ImageLayout::ePresentSrcKHR);

        // 2. 附件引用：子通道内以颜色附件最优布局访问 0 号附件
        vk::AttachmentReference colorRef;
        colorRef.setAttachment(0);
        colorRef.setLayout(vk::ImageLayout::eColorAttachmentOptimal);

        // 3. 子通道描述：唯一的图形子通道，输出到颜色附件
        vk::SubpassDescription subpass;
        subpass.setPipelineBindPoint(vk::PipelineBindPoint::eGraphics);
        subpass.setColorAttachmentCount(1);
        subpass.setPColorAttachments(&colorRef);

        // 4. 子通道依赖：保证外部操作（呈现/获取）完成后，子通道才写入颜色附件
        vk::SubpassDependency dependency;
        dependency.setSrcSubpass(vk::SubpassExternal);
        dependency.setDstSubpass(0);
        dependency.setSrcStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
        dependency.setSrcAccessMask(vk::AccessFlagBits::eNone);
        dependency.setDstStageMask(vk::PipelineStageFlagBits::eColorAttachmentOutput);
        dependency.setDstAccessMask(vk::AccessFlagBits::eColorAttachmentWrite);

        // 5. 创建渲染通道
        vk::RenderPassCreateInfo createInfo;
        createInfo.setAttachmentCount(1);
        createInfo.setPAttachments(&colorAttachment);
        createInfo.setSubpassCount(1);
        createInfo.setPSubpasses(&subpass);
        createInfo.setDependencyCount(1);
        createInfo.setPDependencies(&dependency);

        renderPass = vk::raii::RenderPass(device, createInfo);
    }
}
