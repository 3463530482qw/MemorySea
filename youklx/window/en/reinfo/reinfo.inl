namespace youklx {
    Window& Window::reinfo(windowsinfo& wininfo) {
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
        wininfo.load();
        reinfo(wininfo);
        return *this;
    }
}