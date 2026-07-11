namespace youklx {
    Scene& Scene::清空() {
        查询.clear();

        菜单.clear();

        for (auto& [占位, 句柄] : 私有菜单) {
            FreeLibrary(句柄);
        }
        私有菜单.clear();

        return *this;
    }
}
