namespace youklx {
    Window& Window::init(float standardAspectRatio) {
        //设置宽高比
        aspectRatio = standardAspectRatio;
        //获取桌面大小
        SDL_DisplayID primary_display = SDL_GetPrimaryDisplay();
        mode = SDL_GetDesktopDisplayMode(primary_display);
        //计算桌面长宽高
        if(aspectRatio >= 1 && aspectRatio <= 100) {
            if(mode->w > mode->h * aspectRatio) {
                w = mode->h * 0.9;
                h = w / aspectRatio;
            } else {
                w = mode->w * 0.9;
                h = w / aspectRatio;
            }
        } else if (aspectRatio >= 0 && aspectRatio < 1) {
            if(mode->w > mode->h * aspectRatio) {
                w = mode->h * 0.9;
                h = w * aspectRatio;
            } else {
                w = mode->w * 0.9;
                h = w * aspectRatio;
            }
        } else {
            throw std::runtime_error("Erro:standardAspectRatio the parameter must be between zero and one hundred");
        }
        return *this;
    }
}