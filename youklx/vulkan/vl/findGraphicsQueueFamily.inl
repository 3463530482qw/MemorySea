namespace youklx {
    Vulkan& Vulkan::findGraphicsQueueFamily() {
        // 1. 获取物理设备支持的所有队列族
        auto queueFamilies = physicalDevice->getQueueFamilyProperties();

        // 2. 遍历查找同时支持图形和呈现的队列族
        for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilies.size()); i++) {
            if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
                // **关键检查：该队列族是否支持向表面呈现**
                if (physicalDevice->getSurfaceSupportKHR(i, *surface)) {
                    graphicsFamilyIndex = i;
                    return *this;
                }
            }
        }

        // 3. 若未找到，抛出异常
        throw std::runtime_error("未找到同时支持图形和呈现的队列族");
    }
}