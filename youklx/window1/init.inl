namespace youklx {
    Window& Window::pinit(const float sar) {
        SDL_DisplayID primary_display = SDL_GetPrimaryDisplay();
        mode = SDL_GetDesktopDisplayMode(primary_display);
        //计算桌面长宽高
        if (sar <= 0.01f || sar > 100.0f) {
            throw std::runtime_error("The aspect ratio for creating the window doesn't meet the requirements");
        }
        float target_w, target_h;
        if ((static_cast<float>(mode->w) / static_cast<float>(mode->h)) > sar) {
            target_h = mode->h * 0.9f;
            target_w = target_h * sar;
        } else {
            target_w = mode->w * 0.9f;
            target_h = target_w / sar;
        }
        w = static_cast<int>(target_w);
        h = static_cast<int>(target_h);
        return *this;
    }

    Window& Window::init(const w_init vinit) {
        aspectRatio = vinit.standardAspectRatio;
        return pinit(aspectRatio);
    }
    Window& Window::init(const iw_init vinit) {
        INIReader reader(vinit.ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }
        return pinit(reader.GetReal(vinit.ivrtp, vinit.itp, 1.778));
    }
}