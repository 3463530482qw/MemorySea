//#include "parameters/dll.cpp"
namespace youklx {
    class Scene{
        public:
            std::unordered_map<std::string, std::function<void ()>> dict{}; //函数字典
            std::set<HMODULE> handles{};    //dll文件字典
            std::string ptr;    //场景指针
        public:
            ~Scene();
            Scene& ldll(std::string dll, std::string nfun);
            Scene& ldlli(std::string ini, std::string ivrtp);
    };
}

#include "ldll.cpp"