namespace youklx {
    Vulkan& Vulkan::lstsize(int w, int h) {
        stsizew = w;
        stsizeh = h;
        return *this;
    }

    Vulkan& Vulkan::ilstsize(std::string ini, std::string ivrtp, std::string witp, std::string hitp) {
        //读取配置
        INIReader reader(ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }
        //调用初始化
        lstsize(reader.GetReal(ivrtp, witp, 1600), reader.GetReal(ivrtp, hitp, 900));
        return *this;
    }
}