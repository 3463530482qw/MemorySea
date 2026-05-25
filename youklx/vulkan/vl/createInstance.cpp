namespace youklx {
    Vulkan& Vulkan::createInstance() {
        vk::ApplicationInfo appInfo{
            "MemorySea",
            VK_MAKE_VERSION(1, 0, 0),
            "YouklxEngine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_3
        };

        // 2. 使用 SDL3 获取所需的实例扩展
        Uint32 extCount = 0;
        const char* const* extNames = SDL_Vulkan_GetInstanceExtensions(&extCount);
        std::vector<const char*> extensions(extNames, extNames + extCount);

        // 3. 所需的验证层（调试用）
        std::vector<const char*> layers = {
            "VK_LAYER_KHRONOS_validation"
        };

        // 4. 实例创建信息
        vk::InstanceCreateInfo createInfo{
            {},
            &appInfo,
            static_cast<uint32_t>(layers.size()),
            layers.data(),
            static_cast<uint32_t>(extensions.size()),
            extensions.data()
        };

        // 5. 创建实例
        this->instance.emplace(this->context, createInfo);

        return *this;
    }
}