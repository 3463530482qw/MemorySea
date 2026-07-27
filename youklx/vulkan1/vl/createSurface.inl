namespace youklx {
    Vulkan& Vulkan::createSurface(SDL_Window* window) {
        VkSurfaceKHR rawSurface;
        if (!SDL_Vulkan_CreateSurface(
                window,
                static_cast<VkInstance>(**instance),
                nullptr,
                &rawSurface
            )) {
            throw std::runtime_error(std::string("SDL 创建 Vulkan 表面失败：") + SDL_GetError());
        }

        // 验证 SDL 返回的句柄是否有效
        if (rawSurface == VK_NULL_HANDLE) {
            throw std::runtime_error("SDL_Vulkan_CreateSurface 返回了 VK_NULL_HANDLE");
        }

        surface.emplace(
            *instance,
            static_cast<vk::SurfaceKHR>(rawSurface)
        );

        return *this;
    }
}