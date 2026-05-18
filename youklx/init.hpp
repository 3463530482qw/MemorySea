namespace youklx {
    void sdlinit();
    void init() {
        sdlinit();
    }

    void sdlinit() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            printf("无法初始化 SDL Video 子系统: %s\n", SDL_GetError());
        }
    }
}