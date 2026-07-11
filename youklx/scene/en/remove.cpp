namespace youklx {
    Scene& Scene::remove(const std::string& name) {
        if (ptr == name) {
            return *this;
        }

        dt.erase(name);

        auto it = pe_dt.find(name);
        if (it != pe_dt.end()) {
            FreeLibrary(it->second);
            pe_dt.erase(it);
        }

        return *this;
    }
}
