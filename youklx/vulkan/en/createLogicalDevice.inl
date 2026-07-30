namespace youklx {
    void Vulkan::createLogicalDevice(uint32_t graphicsFamilyIndex) {
        // 1. 队列创建信息（图形与呈现同族，只申请一个队列）
        float queuePriority = 1.0f;
        vk::DeviceQueueCreateInfo queueCreateInfo;
        queueCreateInfo.setQueueFamilyIndex(graphicsFamilyIndex);
        queueCreateInfo.setQueueCount(1);
        queueCreateInfo.setPQueuePriorities(&queuePriority);

        // 2. 启用的设备扩展（窗口渲染必须开启交换链）
        std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        // 3. 设备特性（暂不全开，后续按需启用，如各向异性过滤）
        vk::PhysicalDeviceFeatures deviceFeatures;

        // 4. 设备创建信息
        vk::DeviceCreateInfo deviceCreateInfo;
        deviceCreateInfo.setQueueCreateInfoCount(1);
        deviceCreateInfo.setPQueueCreateInfos(&queueCreateInfo);
        deviceCreateInfo.setPEnabledFeatures(&deviceFeatures);
        deviceCreateInfo.setEnabledExtensionCount(static_cast<uint32_t>(deviceExtensions.size()));
        deviceCreateInfo.setPpEnabledExtensionNames(deviceExtensions.data());

        // 5. 创建逻辑设备，并取出图形队列（呈现复用同一队列）
        device = vk::raii::Device(physicalDevice, deviceCreateInfo);
        graphicsQueue = device.getQueue(graphicsFamilyIndex, 0);
    }
}
