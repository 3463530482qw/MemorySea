namespace youklx {
    Window& Window::create(windowscreateinfo& info) {
        info.load();
        id = SDL_CreateWindow(name.c_str(), w, h, info.flage);
        if (!id) {
            throw std::runtime_error(SDL_GetError());
        }
        return *this;
    }
    Window& Window::create() {
        windowscreateinfo info;
        create(info);
        return *this;
    }
}