namespace youklx {
    void Swapchain::createImageViews(const vk::raii::Device& device) {
        imageViews.clear();
        imageViews.reserve(images.size());

        for (const auto& image : images) {
            // 为每张交换链图像创建 2D 视图，映射颜色通道，仅访问第 0 层 mip、第 0 层 array
            vk::ImageViewCreateInfo viewInfo;
            viewInfo.setImage(image);
            viewInfo.setViewType(vk::ImageViewType::e2D);
            viewInfo.setFormat(format);
            viewInfo.setComponents({
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity,
                vk::ComponentSwizzle::eIdentity
            });
            viewInfo.setSubresourceRange({
                vk::ImageAspectFlagBits::eColor,
                0, 1, 0, 1
            });

            imageViews.emplace_back(device, viewInfo);
        }
    }
}
