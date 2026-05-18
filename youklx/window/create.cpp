namespace youklx {
    void Window::create() {
        id = SDL_CreateWindow(
            "我的第一个 SDL3 窗口",
            800,                       // 窗口宽度
            600,                       // 窗口高度
            0                          // 窗口标志位 (0 表示默认状态)
        );
    }
}