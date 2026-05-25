namespace youklx {
    Vulkan& Vulkan::pickPhysicalDevice() {
        // 1. 获取所有可用的物理设备（GPU）
        auto physicalDevices = this->instance->enumeratePhysicalDevices();

        uint32_t bestScore = 0;   // 最高评分
        size_t bestIndex = 0;     // 最高评分对应的设备索引

        // 2. 遍历所有设备，逐一评分
        for (size_t i = 0; i < physicalDevices.size(); i++) {
            uint32_t score = this->ratePhysicalDevice(physicalDevices[i]);
            if (score > bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        }

        // 3. 选用评分最高的物理设备
        this->physicalDevice.emplace(std::move(physicalDevices[bestIndex]));

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