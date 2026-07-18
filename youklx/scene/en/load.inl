namespace youklx {
    Scene& Scene::load(const std::string& dll, const std::string& nfun) {
        pe_load(dll, nfun);
        return *this;
    }

    Scene& Scene::iload(const std::string& ini, const std::string& ivrtp) {
        Cshload ca;
        ca.givrtp = ivrtp;

        if (ini_parse(ini.c_str(), pe_sh_load, &ca) < 0) {
            std::cerr << "Error parsing config file: " << ini << std::endl;
            return *this;
        }

        for (auto& [key, dll_path] : ca.viload) {
            if (dll_path.empty()) continue;
            pe_load(dll_path, key);
        }
        return *this;
    }
}