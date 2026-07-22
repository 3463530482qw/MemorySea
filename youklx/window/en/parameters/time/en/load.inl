namespace youklx {
    Time& Time::load() {
        tfps = 0.01666;
        youkft = true;
        return *this;
    }
    Time& Time::iload(const std::string& ini, const std::string& ivrtp) {
        INIReader reader(ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }

        tfps   = 1.0f / reader.GetReal(ivrtp, "fps", 60.0f);
        youkft = reader.GetBoolean(ivrtp, "youkft", true);

        return *this;
    }
}