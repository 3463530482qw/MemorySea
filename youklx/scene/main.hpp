#include"en/parameters/cload.cpp"
#include"中文/参数/类加载.cpp"
namespace youklx {
    class Scene{
        public:
            #include"en/api/var.cpp"
            #include"中文/接口/变量.cpp"
        public:
            #include"en/api/function.cpp"
            #include"中文/接口/函数.cpp"
        private:
            #include "en/api/internal/var.cpp"
        private:
            #include "en/api/internal/function.cpp"
        public:
            ~Scene();
    };
    using 场景 = Scene;
}
#include"main.cpp"
#include"en/remove.cpp"
#include"中文/删除.cpp"
#include"en/clear.cpp"
#include"中文/清空.cpp"
#include"en/pe_load.cpp"
#include"en/load.cpp"
#include"中文/加载.cpp"