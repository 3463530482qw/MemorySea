namespace youklx {
    Window& Window::resize(float nw, float nh) {
        // 0,0 时根据显示器模式自动计算（保持16:9）
        if(nw == 0 && nh == 0) {
            if ((static_cast<float>(mode->w) / static_cast<float>(mode->h)) > 1.7778f) {
                nh = mode->h * 0.9f;
                nw = nh * 1.7778f;
            } else {
                nw = mode->w * 0.9f;
                nh = nw / 1.7778f;
            }
        } else if(nw > 0 && nh > 0 && nw < 1 && nh < 1) {
            // 0~1之间的值视为显示器比例
            nw = mode->w * nw;
            nh = mode->h * nh;
        }
        w = static_cast<int>(nw);
        h = static_cast<int>(nh);
        aspectratio = static_cast<float>(w) / static_cast<float>(h);
        if(!SDL_SetWindowSize(id, w, h)) {
            throw std::runtime_error("Window resize failed");
        }
        return *this;
    }
}
