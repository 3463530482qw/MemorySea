namespace youklx {
    Scene& Scene::删除(const std::string& 名称) {
        if (查询 == 名称) {
            return *this;
        }

        菜单.erase(名称);

        auto 找 = 私有菜单.find(名称);
        if (找 != 私有菜单.end()) {
            FreeLibrary(找->second);
            私有菜单.erase(找);
        }

        return *this;
    }
}
