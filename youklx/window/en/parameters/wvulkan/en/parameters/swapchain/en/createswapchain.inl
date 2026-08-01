namespace youklx {
    void Swapchain::createSwapchain() {
        // 1. 查询交换链支持详情
        auto capabilities = physicalDevice->getSurfaceCapabilitiesKHR(*surface);
        auto formats = physicalDevice->getSurfaceFormatsKHR(*surface);
        auto presentModes = physicalDevice->getSurfacePresentModesKHR(*surface);

        // 2. 选择表面格式
        // 若唯一格式为 eUndefined，表示无限制，使用最通用的 SRGB 格式
        vk::SurfaceFormatKHR chosenFormat;
        if (formats.size() == 1 && formats[0].format == vk::Format::eUndefined) {
            chosenFormat.format = vk::Format::eB8G8R8A8Srgb;
            chosenFormat.colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
        } else {
            chosenFormat = formats[0];
            for (const auto& f : formats) {
                if (f.format == vk::Format::eB8G8R8A8Srgb &&
                    f.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                    chosenFormat = f;
                    break;
                }
            }
        }
        format = chosenFormat.format;

        // 3. 选择呈现模式（优先 Mailbox 三重缓冲，否则回退到保证可用的 FIFO）
        vk::PresentModeKHR chosenPresentMode = vk::PresentModeKHR::eFifo;
        for (const auto& pm : presentModes) {
            if (pm == vk::PresentModeKHR::eMailbox) {
                chosenPresentMode = pm;
                break;
            }
        }

        // 4. 选择交换范围（限定在硬件能力范围内）
        extent.width = std::clamp(static_cast<uint32_t>(w),
            capabilities.minImageExtent.width,
            capabilities.maxImageExtent.width);
        extent.height = std::clamp(static_cast<uint32_t>(h),
            capabilities.minImageExtent.height,
            capabilities.maxImageExtent.height);

        // 5. 确定图像数量（最小 + 1 实现三重缓冲，不超过硬件上限）
        uint32_t imageCount = capabilities.minImageCount + 1;
        if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
            imageCount = capabilities.maxImageCount;
        }

        // 6. 配置交换链创建信息（图形与呈现同族，默认独占共享模式）
        vk::SwapchainCreateInfoKHR createInfo;
        createInfo.setSurface(*surface);
        createInfo.setMinImageCount(imageCount);
        createInfo.setImageFormat(chosenFormat.format);
        createInfo.setImageColorSpace(chosenFormat.colorSpace);
        createInfo.setImageExtent(extent);
        createInfo.setImageArrayLayers(1);
        createInfo.setImageUsage(vk::ImageUsageFlagBits::eColorAttachment);
        createInfo.setPreTransform(capabilities.currentTransform);
        createInfo.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
        createInfo.setPresentMode(chosenPresentMode);
        createInfo.setClipped(true);

        // 7. 创建交换链并取回图像句柄（交换链自身持有图像所有权）
        swapchain = vk::raii::SwapchainKHR(*device, createInfo);
        images = swapchain.getImages();
    }
}
