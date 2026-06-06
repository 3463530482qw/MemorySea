namespace youklx {
    Window& Window::fps(int sfps) {
        // sfps <= 0 表示关闭软件限帧，time.fps = 0 使限帧逻辑跳过
        time.fps = (sfps > 0) ? (1.0f / static_cast<float>(sfps)) : 0.0f;
        return *this;
    }

    Window& Window::ifps(std::string ini, std::string ivrtp, std::string itp) {
        INIReader reader(ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }
        fps(reader.GetInteger(ivrtp, itp, 60));
        return *this;
    }
}