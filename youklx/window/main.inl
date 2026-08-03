namespace youklx {
    Window::~Window() {
        if (id) { // 未创建窗口(如空壳 main 直接退出)时跳过帧循环,避免解引用空指针崩溃
            run();
            SDL_DestroyWindow(id);
            id = nullptr;
        }
    }
}