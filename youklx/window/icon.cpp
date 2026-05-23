namespace youklx {
    Window& Window::icon(Plimage ima) {
        //取出图片数据
        auto& gima = std::visit(std::identity{}, ima);
        //创建表面
        SDL_Surface* surf = SDL_CreateSurfaceFrom(gima.w, gima.h, SDL_PIXELFORMAT_RGBA32, gima.data, gima.w * 4);
        //设置窗口图标
        SDL_SetWindowIcon(id, surf);
        return *this;
    }
}