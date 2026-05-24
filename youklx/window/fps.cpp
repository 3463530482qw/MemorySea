namespace youklx {
    Window& Window::fps(int sfps) {
        time.fps = 1.0f / static_cast<float>(sfps);
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