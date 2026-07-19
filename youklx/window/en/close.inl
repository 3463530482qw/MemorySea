namespace youklx {
    Window& Window::close() {
        isrun = false;               // 停止事件循环
        run();                       // 处理剩余事件
        if (id) {
            SDL_DestroyWindow(id);   // 销毁 SDL 窗口
            id = nullptr;
        }
        return *this;
    }
}
