namespace youklx {
    Scene& Scene::clear() {
        ptr.clear();

        dt.clear();

        for (auto& [name, handle] : pe_dt) {
            FreeLibrary(handle);
        }
        pe_dt.clear();

        return *this;
    }
}
