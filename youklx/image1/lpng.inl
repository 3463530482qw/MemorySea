namespace youklx {
    // INI 解析回调：收集指定 section 下的所有 key 名
    struct LoadIniCtx {
        std::vector<std::string> keys{};
        std::string targetSection{};
    };
    static int loadIniCb(void* ctx, const char* section, const char* key, const char* /*value*/) {
        auto* c = static_cast<LoadIniCtx*>(ctx);
        if (std::string(section) == c->targetSection) c->keys.push_back(key);
        return 1;
    }

    // 注册所有可用的图片格式加载器（类似 AI 模块的 iact()）
    Image& Image::initLoaders() {
        // PNG 加载器：stb_image 强制转为 4 通道 RGBA
        loaders["png"] = [](const char* path) -> Plimage {
            Plpng img;
            img.data = stbi_load(path, &img.w, &img.h, nullptr, 4);
            img.channels = 4;
            if (!img.data)
                throw std::runtime_error(std::string("load png: ") + stbi_failure_reason());
            return img;
        };
        // 未来扩展只需在此添加：loaders["jpg"] = ...; loaders["bmp"] = ...;
        return *this;
    }

    // 根据扩展名自动选择加载器（类似 AI 的 curact 分发）
    Image& Image::load(const char* path) {
        ima.push_back(std::vector<Plimage>());
        if (loaders.empty()) initLoaders();

        // 提取扩展名
        std::string p(path);
        auto dot = p.find_last_of('.');
        std::string ext = (dot != std::string::npos) ? p.substr(dot + 1) : "png";

        auto it = loaders.find(ext);
        if (it == loaders.end()) {
            std::cerr << "unsupported image format: ." << ext << std::endl;
            return *this;
        }

        try {
            ima.back().push_back(it->second(path));
        } catch (const std::exception& e) {
            std::cerr << "load failed: " << path << " (" << e.what() << ")" << std::endl;
        }
        return *this;
    }

    // 从 INI 配置文件加载一组图片
    Image& Image::load(const std::string& ini, const std::string& section) {
        ima.push_back(std::vector<Plimage>());
        if (loaders.empty()) initLoaders();

        LoadIniCtx ctx;
        ctx.targetSection = section;
        INIReader reader(ini);

        if (ini_parse(ini.c_str(), loadIniCb, &ctx) < 0) {
            std::cerr << "load ini parse error: " << ini << std::endl;
        } else {
            for (auto& key : ctx.keys) {
                std::string path = reader.Get(section, key, "");
                if (path.empty()) continue;

                std::string ext;
                auto dot = path.find_last_of('.');
                ext = (dot != std::string::npos) ? path.substr(dot + 1) : "png";

                auto it = loaders.find(ext);
                if (it == loaders.end()) {
                    std::cerr << "unsupported format: ." << ext << std::endl;
                    continue;
                }

                try {
                    ima.back().push_back(it->second(path.c_str()));
                } catch (const std::exception& e) {
                    std::cerr << "load failed: " << path << " (" << e.what() << ")" << std::endl;
                }
            }
        }
        return *this;
    }
}