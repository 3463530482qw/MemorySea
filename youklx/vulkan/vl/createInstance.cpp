namespace youklx {
    Vulkan& Vulkan::createInstance() {
        //应用信息
       vk::ApplicationInfo appInfo(
            "MemorySea",
            VK_MAKE_VERSION(1, 0, 0),
            "YouklxEngine",
            VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_0
        );

        // 用 SDL 查询所需的 Vulkan 实例扩展（自动包含平台表面扩展）
        uint32_t extensionCount = 0;
        const char* const* sdlExtensions = SDL_Vulkan_GetInstanceExtensions(&extensionCount);
        if (!sdlExtensions) {
            throw std::runtime_error("SDL_Vulkan_GetInstanceExtensions 获取扩展列表失败");
        }
        std::vector<const char*> enabledExtensions(sdlExtensions, sdlExtensions + extensionCount);

        #ifndef NDEBUG
            enabledExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        #endif
            // 可选验证层
            std::vector<const char*> enabledLayers;
        #ifndef NDEBUG
            enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
        #endif

        // InstanceCreateInfo
        vk::InstanceCreateInfo createInfo(
            {},
            &appInfo,
            enabledLayers,
            enabledExtensions
        );

        // 创建实例，RAII 自动管理
        instance.emplace(context, createInfo);
        return *this;
    }
}