namespace youklx {
    Vulkan& Vulkan::createDevice() {
        // 1. 队列优先级
        float queuePriority = 1.0f;
        vk::DeviceQueueCreateInfo queueCreateInfo{
            {},
            this->graphicsFamilyIndex,
            1,
            &queuePriority
        };

        // 2. 所需的设备扩展（交换链是必须的）
        std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        // 3. 设备特性（暂不启用额外特性）
        vk::PhysicalDeviceFeatures deviceFeatures{};

        // 4. 逻辑设备创建信息
        vk::DeviceCreateInfo createInfo{
            {},
            1,
            &queueCreateInfo,
            0,
            nullptr,
            static_cast<uint32_t>(deviceExtensions.size()),  // 扩展数量
            deviceExtensions.data(),                         // 扩展名称
            &deviceFeatures
        };

        // 5. 创建逻辑设备
        this->device.emplace(*this->physicalDevice, createInfo);

        // 6. 获取图形队列
        this->graphicsQueue.emplace(
            (*this->device).getQueue(this->graphicsFamilyIndex, 0)
        );

        return *this;
    }
}