namespace youklx {
    Window& Window::run() {
        // 一次性绑定:字体渲染的字体对象(init 时可能还没加载,首次 run 时绑定)
        if (!wvulkan.fontrender.font) wvulkan.fontrender.font = &font;
        wvulkan.drawVertices = &draw.vertices; // 顶点注入
        wvulkan.logicW = mlx;                 // 逻辑画布尺寸注入(投影用)
        wvulkan.logicH = mly;
        wvulkan.camera = &camera;             // 相机注入(投影变换用)
        wvulkan.drawFrame();
        draw.vertices.clear();
        time.update();
        key.update();
        while (SDL_PollEvent(&pept)) {
            if (pept.window.windowID != 0 && pept.window.windowID != wid) {
                pe.push_back(pept);
                continue;
            }
            switch (pept.type) {
                case SDL_EVENT_QUIT:
                    isrun = false;
                    break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    isrun = false;
                    break;
                case SDL_EVENT_MOUSE_MOTION:
                    mupdate(pept.motion.x,pept.motion.y);
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    mwupdate(pept.window.data1,pept.window.data2); 
                    break;
                case SDL_EVENT_SET_WICON:
                    SDL_SetWindowIcon(id, static_cast<SDL_Surface*>(pept.user.data1));
                    SDL_DestroySurface(static_cast<SDL_Surface*>(pept.user.data1));
                    break;  
                default:
                    break;
            }
        }
        for (auto& e : pe) {  
            SDL_PushEvent(&e);
        }
        pe.clear();
        return *this;
    }
}
