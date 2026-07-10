namespace youklx {
    class Scene{
        public:
            std::unordered_map<std::string, std::function<void ()>> dict{}; //函数字典
            std::unordered_map<std::string, std::function<void ()>>& 菜单{dict};
            std::string ptr;    //场景指针
            std::string& 查询{ptr};
        public:
            ~Scene();
            Scene& ldll(const std::string& dll, const std::string& nfun);
            inline Scene& 添加(const std::string& dll, const std::string& nfun) { return ldll(dll, nfun); }
            Scene& ldlli(const std::string& ini, const std::string& ivrtp);
            inline Scene& 通过配置添加(const std::string& ini, const std::string& ivrtp) { return ldlli(ini, ivrtp); }
            Scene& remove(const std::string& name);
            inline Scene& 移除(const std::string& name) { return remove(name); }
            Scene& clear();
            inline Scene& 清空() { return clear(); }
        private:
            void _load_dll(const std::string& dll, const std::string& nfun);
            std::unordered_map<std::string, HMODULE> handles{};    //场景名→dll文件句柄
    };
    using 场景 = Scene;
}

#include "ldll.cpp"
#include "remove.cpp"
#include "clear.cpp"