namespace youklx {
    Window& Window::positionAdjustment(int px, int py) {
        // 窗口默认居中
        if(px == 0 && py == 0) {
            px = (mode->w - w) * 0.5;
            py = (mode->h - h) * 0.45;
        }
        if(!SDL_SetWindowPosition(id, px, py)) {
            throw std::runtime_error("Position adjustment failed");
        }
        return *this;
    }
}