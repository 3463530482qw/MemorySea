namespace youklx {
    void Window::create(windowcreateinfo &exwindowcreatinfo) {
        // 检测用户填写窗口宽高是否合规
        if(
            exwindowcreatinfo.w > 0 && 
            exwindowcreatinfo.h > 0 && 
            exwindowcreatinfo.w < mode->w &&
            exwindowcreatinfo.h < mode->h
        ) {
            w = exwindowcreatinfo.w;
            h = exwindowcreatinfo.h;
        }
        id = SDL_CreateWindow(
            exwindowcreatinfo.name.c_str(),
            w,                       // 窗口宽度
            h,                       // 窗口高度
            exwindowcreatinfo.flage
        );
        if (!id) {
            throw std::runtime_error(SDL_GetError());  // ← 加这个
        }
    }
}