namespace youklx {
    void init() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(std::string("无法初始化 SDL Video 子系统: ") + SDL_GetError());
        }
    }
}
