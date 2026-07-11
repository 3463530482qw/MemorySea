namespace youklx {
    class Scene{
        public:
            std::unordered_map<std::string, std::function<void ()>> dt{};
            std::unordered_map<std::string, std::function<void ()>>& 菜单{dt};
            std::string ptr;
            std::string& 查询{ptr};
        public:
            Scene& load(const std::string& dll, const std::string& nfun);
            Scene& iload(const std::string& ini, const std::string& ivrtp);
            Scene& remove(const std::string& name);
            Scene& clear();
        private:
            std::unordered_map<std::string, HMODULE> pe_dt{};
        private:
            void pe_load(const std::string& dll, const std::string& nfun);
            static int pe_sh_load(void* ini, const char* ivrtp, const char* itype, const char* value);
        public:
            ~Scene();
    };
    using 场景 = Scene;
}
#include"main.cpp"
#include"remove.cpp"
#include"clear.cpp"
#include"en/parameters/cload.cpp"
#include"中文/参数/cload.cpp"
#include"en/pe_load.cpp"
#include"en/load.cpp"