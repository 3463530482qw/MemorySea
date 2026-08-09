namespace youklx {
    uint32_t FontRender::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags flags) const {
        vk::PhysicalDeviceMemoryProperties props = physicalDevice->getMemoryProperties();
        for (uint32_t i = 0; i < props.memoryTypeCount; i++) {
            if ((typeFilter & (1u << i)) && (props.memoryTypes[i].propertyFlags & flags) == flags)
                return i;
        }
        throw std::runtime_error("未找到满足要求的内存类型");
    }
}
