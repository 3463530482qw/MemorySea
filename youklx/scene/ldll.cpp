namespace youklx {

// 私有辅助：加载单个 DLL 并将指定函数注册到菜单字典
void Scene::_load_dll(const std::string& dll, const std::string& nfun) {
    auto handle = IL_DLL(dll.c_str());
    if (!handle) {
        std::cerr << "Failed to load DLL: " << dll << std::endl;
        return;
    }
    auto func = reinterpret_cast<void(*)()>(IG_FUNC(handle, nfun.c_str()));
    if (func) {
        dict[nfun] = func;
        handles[nfun] = handle;
    } else {
        std::cerr << "Function " << nfun << " not found in " << dll << std::endl;
        IC_DLL(handle);
    }
}

Scene& Scene::ldll(const std::string& dll, const std::string& nfun) {
    _load_dll(dll, nfun);
    return *this;
}

// ini_parse 回调：收集指定节下的键值对（一次解析同时拿到 key 和 value）
struct Clildll {
    std::string givrtp;
    std::vector<std::pair<std::string, std::string>> vildll;
};

static int lildll(void* ini, const char* ivrtp, const char* itype, const char* value) {
    auto* data = static_cast<Clildll*>(ini);
    if (data->givrtp == ivrtp) {
        data->vildll.emplace_back(itype, value);
    }
    return 1;
}

Scene& Scene::ldlli(const std::string& ini, const std::string& ivrtp) {
    Clildll ca;
    ca.givrtp = ivrtp;

    // 只解析一次 INI，回调中同时收集键和值，无需 INIReader 二次解析
    if (ini_parse(ini.c_str(), lildll, &ca) < 0) {
        std::cerr << "Error parsing config file: " << ini << std::endl;
        return *this;
    }

    for (auto& [key, dll_path] : ca.vildll) {
        if (dll_path.empty()) continue;
        _load_dll(dll_path, key);
    }
    return *this;
}

Scene::~Scene() {
    for (auto& [name, handle] : handles) {
        IC_DLL(handle);
    }
}

}
