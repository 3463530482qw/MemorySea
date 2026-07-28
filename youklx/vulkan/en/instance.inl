namespace youklx {
    void Vulkan::creatInstance(itvinfo ivinfo) {
        // 应用信息
        vk::ApplicationInfo appInfo = vk::ApplicationInfo()
            .setPApplicationName(ivinfo.wname.c_str())
            .setApplicationVersion(VK_MAKE_VERSION(1, 0, 0))
            .setPEngineName("No Engine")
            .setEngineVersion(VK_MAKE_VERSION(1, 0, 0))
            .setApiVersion(VK_API_VERSION_1_4);

        // layer 列表（内部管理，不对外暴露）
        std::vector<const char*> layers = {};
        #ifndef NDEBUG
            ivinfo.extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            layers.push_back("VK_LAYER_KHRONOS_validation");
        #endif

        vk::ValidationFeaturesEXT validationFeatures;
        #ifndef NDEBUG
            std::vector<vk::ValidationFeatureEnableEXT> enabledValidationFeatures = {
                vk::ValidationFeatureEnableEXT::eBestPractices,
                vk::ValidationFeatureEnableEXT::eSynchronizationValidation,
            };
            validationFeatures.setEnabledValidationFeatures(enabledValidationFeatures);
        #endif

        vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        #ifndef NDEBUG
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
        createInfo.setPpEnabledLayerNames(layers.data());
        createInfo.setEnabledExtensionCount(static_cast<uint32_t>(ivinfo.extensions.size()));
        createInfo.setPpEnabledExtensionNames(ivinfo.extensions.data());
        #ifndef NDEBUG
            createInfo.setPNext(&debugCreateInfo);
        #endif

        instance = vk::raii::Instance(context, createInfo);
    }
}