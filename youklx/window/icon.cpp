namespace youklx {
    Window& Window::icon(Plimage ima) {
        auto& gima = std::visit(std::identity{}, ima);
        // 创建自带像素缓冲区的表面（拷贝数据，不依赖外部生命周期）
        SDL_Surface* surf = SDL_CreateSurface(gima.w, gima.h, SDL_PIXELFORMAT_RGBA32);
        if (!surf) {
            std::cerr << "创建窗口图标表面失败: " << SDL_GetError() << std::endl;
            return *this;
        }
        memcpy(surf->pixels, gima.data, gima.w * gima.h * 4);
        // 推入事件队列，由 run() 统一设置图标并销毁表面
        pe.type = SDL_EVENT_USER;
        pe.user.code = 1;
        pe.user.data1 = surf;
        SDL_PushEvent(&pe);
        return *this;
    }
}

