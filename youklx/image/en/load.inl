namespace youklx {
    Image& Image::load(const char* path) {
        Plimage img;
        img.data = stbi_load(path, &img.w, &img.h, nullptr, 4);
        if (!img.data) {
            throw std::runtime_error(std::string("图片加载失败: ") + path + " (" + stbi_failure_reason() + ")");
        }
        ima.emplace_back();
        ima.back().push_back(img);
        return *this;
    }
    Image& Image::load(const std::string& ini, const std::string& ivrtp) {
        Cshload ca;
        ca.givrtp = ivrtp;

        if (ini_parse(ini.c_str(), im_sh_load, &ca) < 0) {
            std::cerr << "Error parsing config file: " << ini << std::endl;
            return *this;
        }
        ima.emplace_back();
        for (auto& [key, img_path] : ca.viload) {
            if (img_path.empty()) continue;
            Plimage img;
            img.data = stbi_load(img_path.c_str(), &img.w, &img.h, nullptr, 4);
            if (!img.data) {
                std::cerr << "Failed to load image: " << img_path << " (" << stbi_failure_reason() << ")" << std::endl;
                continue;
            }
            ima.back().push_back(img);
        }
        return *this;
    }

    int Image::im_sh_load(void* ini, const char* ivrtp, const char* itype, const char* value) {
        auto* data = static_cast<Cshload*>(ini);
        if (data->givrtp == ivrtp) {
            data->viload.emplace_back(itype, value);
        }
        return 1;
    }
}