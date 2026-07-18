namespace youklx {
    Window& Window::lstsize(const w_lstsize vlstsize) {
        stsizew = vlstsize.w;
        stsizeh = vlstsize.h;
        return *this;
    }

    Window& Window::lstsize(const iw_lstsize vlstsize) {
        INIReader reader(vlstsize.ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }
        lstsize({reader.GetInteger(vlstsize.ivrtp, vlstsize.witp, 1600), reader.GetInteger(vlstsize.ivrtp, vlstsize.hitp, 900)});
        return *this;
    }
}