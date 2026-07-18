namespace youklx {
    Window::Window() {} // 显示器列表延迟到 reinfo() 中初始化（需在 SDL_Init 之后）
    Window::~Window() {
        if (id) {
            SDL_DestroyWindow(id);
            id = nullptr;
        }
    }
}