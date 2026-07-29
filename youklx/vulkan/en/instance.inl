namespace youklx {
    void Vulkan::createInstance(itvinfo& ivinfo) {
        // 应用信息
        vk::ApplicationInfo appInfo = vk::ApplicationInfo()
            .setPApplicationName(ivinfo.wname.c_str())
            .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
            .setPEngineName("No Engine")
            .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
            .setApiVersion(VK_API_VERSION_1_4);

        uint32_t sdlExtCount = 0;
        auto* sdlExts = SDL_Vulkan_GetInstanceExtensions(&sdlExtCount);
        if (!sdlExts) throw std::runtime_error("SDL_Vulkan_GetInstanceExtensions failed");

        std::vector<const char*> layers;
        ivinfo.extensions.insert(ivinfo.extensions.end(), sdlExts, sdlExts + sdlExtCount);

        #ifndef NDEBUG
            ivinfo.extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            layers.push_back("VK_LAYER_KHRONOS_validation");

            vk::ValidationFeaturesEXT validationFeatures;
            std::vector<vk::ValidationFeatureEnableEXT> enabledValidationFeatures = {
                vk::ValidationFeatureEnableEXT::eBestPractices,
                vk::ValidationFeatureEnableEXT::eSynchronizationValidation,
            };
            validationFeatures.setEnabledValidationFeatures(enabledValidationFeatures);

            vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo;
            debugCreateInfo.setMessageSeverity(
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
            );
            debugCreateInfo.setMessageType(
                vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
            );
            debugCreateInfo.setPNext(&validationFeatures);
        #endif

        // 实例创建信息
        vk::InstanceCreateInfo createInfo;
        createInfo.setPApplicationInfo(&appInfo);
        createInfo.setEnabledLayerCount(static_cast<uint32_t>(layers.size()));
        createInfo.setPpEnabledLayerNames(layers.empty() ? nullptr : layers.data());
        createInfo.setEnabledExtensionCount(static_cast<uint32_t>(ivinfo.extensions.size()));
        createInfo.setPpEnabledExtensionNames(ivinfo.extensions.empty() ? nullptr : ivinfo.extensions.data());
        #ifndef NDEBUG
            createInfo.setPNext(&debugCreateInfo);
        #endif

        instance = vk::raii::Instance(context, createInfo);
    }
}