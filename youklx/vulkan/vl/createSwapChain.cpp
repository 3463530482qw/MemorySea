namespace youklx {
    Vulkan& Vulkan::createSwapChain() {
        if (!surface ||
            static_cast<VkSurfaceKHR>(**surface) == VK_NULL_HANDLE) {
            throw std::runtime_error("createSwapChain: surface 无效");
        }

        auto capabilities = physicalDevice->getSurfaceCapabilitiesKHR(*surface);
        auto formats = physicalDevice->getSurfaceFormatsKHR(*surface);
        auto presentModes = physicalDevice->getSurfacePresentModesKHR(*surface);

        // 选择表面格式
        swapChainImageFormat = vk::Format::eB8G8R8A8Srgb;
        vk::ColorSpaceKHR colorSpace = vk::ColorSpaceKHR::eSrgbNonlinear;
        for (const auto& f : formats) {
            if (f.format == vk::Format::eB8G8R8A8Srgb &&
                f.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                swapChainImageFormat = f.format;
                colorSpace = f.colorSpace;
                break;
            }
        }

        // 选择呈现模式
        vk::PresentModeKHR presentMode = vk::PresentModeKHR::eFifo;
        for (const auto& m : presentModes) {
            if (m == vk::PresentModeKHR::eMailbox) {
                presentMode = m;
                break;
            }
        }

        // 直接使用 stsizew 与 stsizeh 作为交换链尺寸
        uint32_t extentW = static_cast<uint32_t>(stsizew);
        uint32_t extentH = static_cast<uint32_t>(stsizeh);

        // 钳位到表面能力允许的范围
        extentW = std::clamp(extentW,
            capabilities.minImageExtent.width,
            capabilities.maxImageExtent.width);
        extentH = std::clamp(extentH,
            capabilities.minImageExtent.height,
            capabilities.maxImageExtent.height);

        this->swapChainExtent = vk::Extent2D{extentW, extentH};

        // 确定图像数量
        uint32_t imageCount = capabilities.minImageCount + 1;
        if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
            imageCount = capabilities.maxImageCount;
        }

        vk::SwapchainCreateInfoKHR createInfo{
            {},
            *this->surface,
            imageCount,
            this->swapChainImageFormat,
            colorSpace,
            this->swapChainExtent,
            1,
            vk::ImageUsageFlagBits::eColorAttachment,
            vk::SharingMode::eExclusive,
            0,
            nullptr,
            capabilities.currentTransform,
            vk::CompositeAlphaFlagBitsKHR::eOpaque,
            presentMode,
            VK_TRUE,
            nullptr
        };

        this->swapChain = this->device->createSwapchainKHR(createInfo);

        this->swapChainImages = (*this->swapChain).getImages();
        for (const auto& image : this->swapChainImages) {
            vk::ImageViewCreateInfo viewCreateInfo{
                {},
                image,
                vk::ImageViewType::e2D,
                this->swapChainImageFormat,
                {},
                {vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1}
            };
            this->swapChainImageViews.emplace_back(*this->device, viewCreateInfo);
        }

        return *this;
    }
}