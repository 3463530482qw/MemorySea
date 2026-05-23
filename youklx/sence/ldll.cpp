namespace youklx {
    Sence& Sence::ldll(std::string pdll, std::string nfun) {
        auto handle = ildll(pdll.c_str());
        void (*func)() = (void(*)())igfunc(handle, nfun.c_str());
        if (func) {
            dict[nfun] = func;
            handles.insert(handle); 
        }
        return *this;
    }

    Sence::~Sence() {
        for (void* handle : handles) {
            if (handle) {
                icdll(handle);
            }
        }
    }
}
    