namespace youklx {
    Vulkan& Vulkan::createSwapChain() {
        if (!surface) throw std::runtime_error("createSwapChain: surface 无效");

        auto capabilities = physicalDevice->getSurfaceCapabilitiesKHR(*surface);
        auto formats      = physicalDevice->getSurfaceFormatsKHR(*surface);
        auto presentModes = physicalDevice->getSurfacePresentModesKHR(*surface);

        // 选择表面格式（优先 sRGB 非线性）
        vk::ColorSpaceKHR colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
        for (const auto& f : formats) {
            if (f.format == vk::Format::eB8G8R8A8Srgb &&
                f.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                colorSpace = f.colorSpace; break;
            }
        }
        swapChainImageFormat = vk::Format::eB8G8R8A8Srgb;

        // 选择呈现模式（优先 Mailbox 低延迟，否则回退 FIFO）
        vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
        for (const auto& m : presentModes) {
            if (m == vk::PresentModeKHR::eMailbox) { presentMode = m; break; }
        }

        // 交换链尺寸：钳位到表面能力范围
        uint32_t extentW = std::clamp(static_cast<uint32_t>(stsizew),
            capabilities.minImageExtent.width,
            capabilities.maxImageExtent.width);
        uint32_t extentH = std::clamp(static_cast<uint32_t>(stsizeh),
            capabilities.minImageExtent.height,
            capabilities.maxImageExtent.height);
        swapChainExtent = vk::Extent2D{extentW, extentH};

        // 交换链图像数量（min+1 以获得更好的缓冲）
        uint32_t imageCount = capabilities.minImageCount + 1;
        if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
            imageCount = capabilities.maxImageCount;

        // 创建交换链（完成后立即创建对应的图像视图）
        swapChain = device->createSwapchainKHR(
            vk::SwapchainCreateInfoKHR{{}, *surface, imageCount,
                swapChainImageFormat, colorSpace, swapChainExtent, 1,
                vk::ImageUsageFlagBits::eColorAttachment,
                vk::SharingMode::eExclusive, 0, nullptr,
                capabilities.currentTransform,
                vk::CompositeAlphaFlagBitsKHR::eOpaque,
                presentMode, VK_TRUE, nullptr});

        swapChainImages = (*swapChain).getImages();
        for (const auto& img : swapChainImages) {
            swapChainImageViews.emplace_back(*device,
                vk::ImageViewCreateInfo{{}, img, vk::ImageViewType::e2D,
                    swapChainImageFormat, {},
                    {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}});
        }
        return *this;
    }
}