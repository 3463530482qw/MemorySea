namespace youklx {
    windowsinfo& windowsinfo::initi(const std::string& ini, const std::string& ivrtp) {
        INIReader reader(ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }

        name          = reader.Get(ivrtp, "name", "a window");
        w             = reader.GetInteger(ivrtp, "w", 0);
        h             = reader.GetInteger(ivrtp, "h", 0);
        //icon          = reader.Get(ivrtp, "icon", "null");
        display_index = static_cast<uint8_t>(reader.GetUnsigned(ivrtp, "display_index", 0));

        return *this;
    }
}