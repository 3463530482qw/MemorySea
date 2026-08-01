// 1. 获取物理设备支持的所有队列族
auto queueFamilies = vulkan.physicalDevice.getQueueFamilyProperties();

// 2. 遍历查找同时支持图形和呈现的队列族
bool found = false;
for (uint32_t i = 0; i < static_cast<uint32_t>(queueFamilies.size()); i++) {
    if (queueFamilies[i].queueFlags & vk::QueueFlagBits::eGraphics) {
        // **关键检查：该队列族是否支持向表面呈现**
        if (vulkan.physicalDevice.getSurfaceSupportKHR(i, *surface)) {
            graphicsFamilyIndex = i;
            found = true;
            break; // 找到后跳出循环（不能 return，本文件被内联进 init 函数体）
        }
    }
}

// 3. 若未找到，抛出异常
if (!found) {
    throw std::runtime_error("未找到同时支持图形和呈现的队列族");
}