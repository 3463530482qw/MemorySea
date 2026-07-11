namespace youklx {
    void Scene::pe_load(const std::string& dll, const std::string& nfun) {
        auto handle = LoadLibraryA(dll.c_str());
        if (!handle) {
            std::cerr << "Failed to load DLL: " << dll << std::endl;
            return;
        }
        auto func = reinterpret_cast<void(*)()>(GetProcAddress(handle, nfun.c_str()));
        if (func) {
            dt[nfun] = func;
            pe_dt[nfun] = handle;
        } else {
            std::cerr << "Function " << nfun << " not found in " << dll << std::endl;
            FreeLibrary(handle);
        }
    }

    int Scene::pe_sh_load(void* ini, const char* ivrtp, const char* itype, const char* value){
        auto* data = static_cast<Cshload*>(ini);
        if (data->givrtp == ivrtp) {
            data->viload.emplace_back(itype, value);
        }
        return 1;
    }
}