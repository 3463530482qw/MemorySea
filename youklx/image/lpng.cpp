namespace youklx {
    struct Clilpng {
        std::vector<std::string> vilpng{};
        std::string givrtp{};
    };

    static int lilpng(void* ini, const char* ivrtp, const char* itype, const char* value) {
        Clilpng* data = static_cast<Clilpng*>(ini);
        if (std::string(ivrtp) == data->givrtp) {
            data->vilpng.push_back(itype);
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

    Image& Image::ilpng(std::string ini, std::string ivrtp) {
        ima.push_back(std::vector<Plimage>());
        Clilpng ca;
        ca.givrtp = ivrtp;
        Plpng imapng;
        INIReader reader(ini);
        if (ini_parse(ini.c_str(), lilpng, &ca) < 0) {
            std::cerr << "Error parsing config file." << std::endl;
        } else {
            for (auto& ilpng : ca.vilpng) {
                ilpng = reader.Get(ivrtp, ilpng, "");
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