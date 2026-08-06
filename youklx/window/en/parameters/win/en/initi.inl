namespace youklx {
    windowsinfo& windowsinfo::initi(const INIReader& reader, const std::string& ivrtp) {
        name          = reader.Get(ivrtp, "name", "a window");
        w             = reader.GetInteger(ivrtp, "w", 0);
        h             = reader.GetInteger(ivrtp, "h", 0);
        mlx           = reader.GetInteger(ivrtp, "mlx", 1600);
        mly           = reader.GetInteger(ivrtp, "mly", 900);
        icon          = reader.Get(ivrtp, "icon", "null");
        display_index = static_cast<uint8_t>(reader.GetUnsigned(ivrtp, "display_index", 0));

        return *this;
    }
}