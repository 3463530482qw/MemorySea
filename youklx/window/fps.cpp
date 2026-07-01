namespace youklx {
    Window& Window::fps(const w_fps vfps) {
        // fps <= 0 表示关闭软件限帧，time.fps = 0 使限帧逻辑跳过
        time.fps = (vfps.fps > 0) ? (1.0f / static_cast<float>(vfps.fps)) : 0.0f;
        return *this;
    }
    Window& Window::fps(const iw_fps vfps) {
        INIReader reader(vfps.ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }
        fps({reader.GetInteger(vfps.ivrtp, vfps.itp, 60)});
        return *this;
    }
}