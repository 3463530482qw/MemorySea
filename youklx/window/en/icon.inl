namespace youklx {
    Window& Window::icon(Plimage ima) {
        SDL_Surface* surf = SDL_CreateSurface(ima.w, ima.h, SDL_PIXELFORMAT_RGBA32);
        if (!surf) {
            std::cerr << "创建窗口图标表面失败: " << SDL_GetError() << std::endl;
            return *this;
        }
        memcpy(surf->pixels, ima.data, ima.w * ima.h * 4);
        pept.type = SDL_EVENT_USER;
        pept.user.code = 1;
        pept.user.data1 = surf;
        pept.user.windowID = wid;
        SDL_PushEvent(&pept);
        return *this;
    }
}