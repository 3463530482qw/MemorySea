namespace youklx {
    void Scene::通用加载(const std::string& dll文件路径, const std::string& 函数名) {
        auto handle = LoadLibraryA(dll文件路径.c_str());
        if (!handle) {
            std::cerr << "未成功加载: " << dll文件路径 << " 喵 " << std::endl;
            return;
        }
        auto 函数 = reinterpret_cast<void(*)()>(GetProcAddress(handle, 函数名.c_str()));
        if (函数) {
            菜单[函数名] = 函数;
            私有菜单[函数名] = handle;
        } else {
            std::cerr << "未找到 " << 函数名 << " 在 " << dll文件路径 << " 喵 " << std::endl;
            FreeLibrary(handle);
        }
    }

    int Scene::键收集(void* ini文件路径, const char* 标签名, const char* 键名, const char* 场景){
        auto* data = static_cast<搜集键*>(ini文件路径);
        if (data->键名 == 标签名) {
            data->加载组.emplace_back(键名, 场景);
        }
        return 1;
    }
}