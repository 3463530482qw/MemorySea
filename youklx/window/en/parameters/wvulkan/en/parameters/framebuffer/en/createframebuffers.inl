namespace youklx {
    void Framebuffer::createFramebuffers() {
        framebuffers.clear();
        framebuffers.reserve(imageViews->size());

        // 为每个交换链图像视图创建一个帧缓冲
        // 帧缓冲把「渲染通道的附件约定」与「具体的图像视图」绑定起来
        for (const auto& imageView : *imageViews) {
            vk::ImageView attachments[] = { *imageView };

            vk::FramebufferCreateInfo createInfo;
            createInfo.setRenderPass(**renderPass);
            createInfo.setAttachmentCount(1);
            createInfo.setPAttachments(attachments);
            createInfo.setWidth(extent->width);
            createInfo.setHeight(extent->height);
            createInfo.setLayers(1);

            framebuffers.emplace_back(*device, createInfo);
        }
    }
}