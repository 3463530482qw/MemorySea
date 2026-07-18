namespace youklx {
    Vulkan& Vulkan::createDevice() {
        // 队列创建信息（图形队列，单一优先级）
        float queuePriority = 1.0f;
        vk::DeviceQueueCreateInfo queueInfo{{}, graphicsFamilyIndex, 1, &queuePriority};

        // 所需设备扩展
        std::vector<const char*> extensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};

        // 设备特性（未启用可选特性；future：samplerAnisotropy、geometryShader）
        vk::PhysicalDeviceFeatures features{};

        // 创建逻辑设备 + 获取图形队列句柄
        device.emplace(*physicalDevice,
            vk::DeviceCreateInfo{{}, 1, &queueInfo, 0, nullptr,
                static_cast<uint32_t>(extensions.size()), extensions.data(), &features});
        graphicsQueue.emplace(device->getQueue(graphicsFamilyIndex, 0));
        return *this;
    }
}