namespace youklx {
    // 按类型过滤位与属性要求挑选内存类型(通用工具,贴图/缓冲分配共用)
    inline uint32_t findMemoryType(vk::raii::PhysicalDevice& pd, uint32_t typeFilter, vk::MemoryPropertyFlags flags) {
        vk::PhysicalDeviceMemoryProperties props = pd.getMemoryProperties();
        for (uint32_t i = 0; i < props.memoryTypeCount; i++) {
            if ((typeFilter & (1u << i)) && (props.memoryTypes[i].propertyFlags & flags) == flags)
                return i;
        }
        throw std::runtime_error("未找到满足要求的内存类型");
    }
}
