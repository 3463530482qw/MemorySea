namespace youklx {

    static int lilpng(void* ini, const char* ivrtp, const char* itype, const char* value) {
        std::vector<std::string>* data = static_cast<std::vector<std::string>*>(ini);
        if (std::string(ivrtp) == "lpng") {
            data->push_back(itype);
        }
        return 1;
    }

    Image& Image::lpng(const char* image) {
        ima.push_back(std::vector<Plimage>());
        Plpng imapng;
        imapng.data = stbi_load(image, &imapng.w, &imapng.h, &imapng.channels, imapng.desired_channels);
        
        
        if (imapng.data == nullptr) {
            std::cerr << "加载图片失败: " << stbi_failure_reason() << std::endl;
        } else {
            ima.back().push_back(imapng);
        }
        return *this;
    }

    Image& Image::ilpng(std::string ini) {
        ima.push_back(std::vector<Plimage>());
        std::vector<std::string> vilpng;
        Plpng imapng;
        INIReader reader(ini);
        if (ini_parse(ini.c_str(), lilpng, &vilpng) < 0) {
            std::cerr << "Error parsing config file." << std::endl;
        } else {
            for (auto& ilpng : vilpng) {
                ilpng = reader.Get("lpng", ilpng, "");
                imapng.data = stbi_load(ilpng.c_str(), &imapng.w, &imapng.h, &imapng.channels, imapng.desired_channels);
                if (imapng.data == nullptr) {
                    std::cerr << "加载图片失败: " << stbi_failure_reason() << std::endl;
                } else {
                    ima.back().push_back(imapng);
                }
            }
        }
        return *this;
    }
}