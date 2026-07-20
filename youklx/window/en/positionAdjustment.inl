namespace youklx {
    Window& Window::positionAdjustment(float px, float py) {
        // 窗口默认居中
        if(px == 0 && py == 0) {
            px = (mode->w - w) * 0.5;
            py = (mode->h - h) * 0.45;
        } else if(px > 0 && py > 0 && px < 1 && py < 1) {
            px = mode->w * px;
            py = mode->h * py;
        }
        if(!SDL_SetWindowPosition(id, static_cast<int>(px), static_cast<int>(py))) {
            throw std::runtime_error("Position adjustment failed");
        }
        return *this;
    }
}
