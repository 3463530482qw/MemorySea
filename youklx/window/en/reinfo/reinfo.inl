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
        icon = wininfo.icon;
        // 一次性绑定绘图数据源(用户随后自行调 wvulkan.init,这里只绑引用,不依赖 init 时机)
        wvulkan.logicW = &mlx;
        wvulkan.logicH = &mly;
        wvulkan.camera = &camera;
        wvulkan.fontrender.camera = &camera;
        wvulkan.drawVertices = &draw.vertices;
        wvulkan.drawBatches = &draw.batches;
        wvulkan.defaultFont = &font;

        return *this;
    }
    Window& Window::reinfo() {
        windowsinfo wininfo;
        wininfo.load();
        reinfo(wininfo);
        return *this;
    }
}