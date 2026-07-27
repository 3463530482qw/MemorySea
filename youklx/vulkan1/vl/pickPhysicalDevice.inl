namespace youklx {
    Vulkan& Vulkan::pickPhysicalDevice() {
        // 1. 获取所有可用的物理设备（GPU）
        auto physicalDevices = instance->enumeratePhysicalDevices();

        if (physicalDevices.empty()) {
            throw std::runtime_error("未找到任何支持 Vulkan 的物理设备(GPU)");
        }

        uint32_t bestScore = 0;
        size_t bestIndex = 0;
        bool foundSuitable = false;

        // 2. 遍历所有设备，逐一评分（仅考虑支持 swapchain 的设备）
        for (size_t i = 0; i < physicalDevices.size(); i++) {
            // 检查设备是否支持 swapchain 扩展（窗口渲染必需）
            auto deviceExtensions = physicalDevices[i].enumerateDeviceExtensionProperties();
            bool hasSwapchain = false;
            for (const auto& ext : deviceExtensions) {
                if (strcmp(ext.extensionName, VK_KHR_SWAPCHAIN_EXTENSION_NAME) == 0) {
                    hasSwapchain = true;
                    break;
                }
            }
            if (!hasSwapchain) continue;  // 不支持 swapchain，跳过

            uint32_t score = ratePhysicalDevice(physicalDevices[i]);
            if (score > bestScore || !foundSuitable) {
                bestScore = score;
                bestIndex = i;
                foundSuitable = true;
            }
        }

        if (!foundSuitable) {
            throw std::runtime_error("未找到支持 VK_KHR_swapchain 扩展的物理设备，请更新显卡驱动");
        }

        // 3. 选用评分最高的物理设备
        physicalDevice.emplace(std::move(physicalDevices[bestIndex]));

        return *this;
    }

    uint32_t Vulkan::ratePhysicalDevice(const vk::raii::PhysicalDevice& device) {
        uint32_t score = 0;

        // 1. 获取设备属性（名称、类型、限制等）
        auto properties = device.getProperties();

        // 2. 获取设备特性（支持的功能）
        auto features = device.getFeatures();

        // 3. 独立显卡优先，给予高分
        if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
            score += 150;
        }

        // 4. 最大纹理尺寸越大越好，按比例加分
        score += properties.limits.maxImageDimension2D / 256;

        // 5. 支持几何着色器则加分
        if (features.geometryShader) {
            score += 50;
        }

        // 6. 支持各向异性过滤则加分
        if (features.samplerAnisotropy) {
            score += 30;
        }

        return score;   // 返回最终评分
    }
}