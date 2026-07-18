namespace youklx {
    Window& Window::fps(const w_fps vfps) {
        time.set_target_fps(vfps.fps);
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