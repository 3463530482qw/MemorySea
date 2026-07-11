namespace youklx {
    Scene::~Scene() {
        for (auto& [name, handle] : pe_dt) {
            FreeLibrary(handle);
        }
    }
}