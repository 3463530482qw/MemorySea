namespace youklx {
    struct Clildll {
        std::vector<std::string> vildll{};
        std::string givrtp{};
    };
    static int lildll(void* ini, const char* ivrtp, const char* itype, const char* value) {
        Clildll* data = static_cast<Clildll*>(ini);
        //如果是指定标签保存对应值
        if (std::string(ivrtp) == data->givrtp) {
            data->vildll.push_back(itype);
        }
        return 1;
    }

    Scene& Scene::ldll(std::string pdll, std::string nfun) {
        // 加载动态链接库，获取句柄
        auto handle = IL_DLL(pdll.c_str());
        if (!handle) {
            std::cerr << "Failed to load DLL: " << pdll << std::endl;
            return *this;
        }
        
        // 获取库中指定名称的函数指针
        void (*func)() = (void(*)())IG_FUNC(handle, nfun.c_str());
        
        // 若函数存在，则注册到字典并保存句柄
        if (func) {
            dict[nfun] = func;       // 记录函数名与函数指针的映射
            handles.insert(handle);  // 保存句柄用于后续释放
        } else {
            std::cerr << "Function " << nfun << " not found in " << pdll << std::endl;
            IC_DLL(handle);  // 函数未找到，释放已加载的 DLL
        }
        
        return *this;
    }
    Scene& Scene::ldlli(std::string ini, std::string ivrtp) {
        Clildll ca;
        //设置ini读取标签名
        ca.givrtp = ivrtp;
        INIReader reader(ini);
        //遍历指定标签加载dll数据
        if (ini_parse(ini.c_str(), lildll, &ca) < 0) {
            std::cerr << "Error parsing config file." << std::endl;
        } else {
            for (auto& dllkey : ca.vildll) {
                auto ildlltp = dllkey;
                dllkey = reader.Get(ivrtp, dllkey, "");
                if (dllkey.empty()) continue;
                auto handle = IL_DLL(dllkey.c_str());
                if (!handle) {
                    std::cerr << "Failed to load DLL: " << dllkey << std::endl;
                    continue;
                }
                void (*func)() = (void(*)())IG_FUNC(handle, ildlltp.c_str());
                if (func) {
                    dict[ildlltp] = func;
                    handles.insert(handle);
                } else {
                    std::cerr << "Function " << ildlltp << " not found in " << dllkey << std::endl;
                    IC_DLL(handle);
                }
            }
        }
        return *this;
    }

    Scene::~Scene() {
        for (void* handle : handles) {
            if (handle) {
                IC_DLL(handle);
            }
        }
    }

}
    