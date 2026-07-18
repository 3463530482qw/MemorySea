namespace youklx {
    Window& Window::reinfo(windowsinfo& wininfo) {
        // 首次调用时初始化显示器列表（确保在 SDL_Init 之后）
        if (displays.empty()) {
            int count = 0;
            SDL_DisplayID* ids = SDL_GetDisplays(&count);
            displays.assign(ids, ids + count);
            SDL_free(ids);
        }
        display_index = (wininfo.display_index < displays.size()) ? wininfo.display_index : 0; // 越界时回退到主显示器
        mode = SDL_GetCurrentDisplayMode(displays[display_index]);
        #include "wh.inl"
        name = wininfo.name;
        return *this;
    }
    Window& Window::reinfo() {
        windowsinfo wininfo;
        reinfo(wininfo);
        return *this;
    }
}