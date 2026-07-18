namespace youklx {
    Window& Window::reinfo(windowsinfo& wininfo) {
        display_index = wininfo.display_index;
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