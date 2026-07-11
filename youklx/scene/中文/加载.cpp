namespace youklx {
    Scene& Scene::加载(const std::string& dll文件路径, const std::string& 函数名) {
        通用加载(dll文件路径, 函数名);
        return *this;
    }

    Scene& Scene::批量加载(const std::string& ini文件路径, const std::string& 标签) {
        搜集键 占位;
        占位.键名 = 标签;

        if (ini_parse(ini文件路径.c_str(), 键收集, &占位) < 0) {
            std::cerr << "没找到文件在: " << ini文件路径 << "喵" << std::endl;
            return *this;
        }

        for (auto& [键, 文件路径] : 占位.加载组) {
            if (文件路径.empty()) continue;
            通用加载(文件路径, 键);
        }
        return *this;
    }
}