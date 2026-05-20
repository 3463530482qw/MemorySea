namespace youklx {
    Window& Window::icon(Plimage ima) {
        auto& gima = std::visit(std::identity{}, ima);
        SDL_Surface* surf = SDL_CreateSurfaceFrom(gima.w, gima.h, SDL_PIXELFORMAT_RGBA32, gima.data, gima.w * 4);
        SDL_SetWindowIcon(id, surf);
        return *this;
    }
}