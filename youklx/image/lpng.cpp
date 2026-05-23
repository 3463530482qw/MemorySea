namespace youklx {
    struct Clilpng {
        std::vector<std::string> vilpng{};
        std::string givrtp{};
    };

    static int lilpng(void* ini, const char* ivrtp, const char* itype, const char* value) {
        Clilpng* data = static_cast<Clilpng*>(ini);
        //如果是指定标签保存对应值
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
        //载入新图片组
        ima.push_back(std::vector<Plimage>());
        //读取的图像数据class load ini load png
        Clilpng ca;
        //设置ini读取标签名
        ca.givrtp = ivrtp;
        //空png图片
        Plpng imapng;
        //读取ini创建INIReader类
        INIReader reader(ini);
        //遍历指定标签加载png数据
        if (ini_parse(ini.c_str(), lilpng, &ca) < 0) {
            std::cerr << "Error parsing config file." << std::endl;
        } else {
            for (auto& ilpng : ca.vilpng) {
                //通过读取的值取出图片路径
                ilpng = reader.Get(ivrtp, ilpng, "");
                //加载图片
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