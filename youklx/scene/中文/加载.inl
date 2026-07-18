namespace youklx {
    Scene& Scene::加载(const std::string& dll文件路径, const std::string& 函数名) {
        return load(dll文件路径, 函数名);
    }

    Scene& Scene::批量加载(const std::string& ini文件路径, const std::string& 标签) {
        return iload(ini文件路径, 标签);
    }
}