namespace youklx {
    Time& Time::load() {
        tfps = 0.01666;
        youkft = true;
        return *this;
    }
    Time& Time::iload(const INIReader& reader, const std::string& ivrtp) {
        tfps   = 1.0f / reader.GetReal(ivrtp, "fps", 60.0f);
        youkft = reader.GetBoolean(ivrtp, "youkft", true);

        return *this;
    }
}