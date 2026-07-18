namespace youklx {
    Vulkan& Vulkan::createInstance() {
        vk::ApplicationInfo appInfo(
            "MemorySea", VK_MAKE_VERSION(1, 0, 0),
            "YouklxEngine", VK_MAKE_VERSION(1, 0, 0),
            VK_API_VERSION_1_3);

        // SDL 查询所需的 Vulkan 实例扩展（自动包含平台表面扩展）
        uint32_t extCount = 0;
        auto* sdlExts = SDL_Vulkan_GetInstanceExtensions(&extCount);
        if (!sdlExts) throw std::runtime_error("SDL_Vulkan_GetInstanceExtensions failed");
        std::vector<const char*> extensions(sdlExts, sdlExts + extCount);

        // Debug 模式：启用校验层和调试扩展
        std::vector<const char*> layers;
    #ifndef NDEBUG
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        layers.push_back("VK_LAYER_KHRONOS_validation");
    #endif

        instance.emplace(context,
            vk::InstanceCreateInfo{{}, &appInfo, layers, extensions});
        return *this;
    }
}