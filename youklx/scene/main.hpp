#include"en/parameters/cload.inl"
#include"中文/参数/类加载.inl"
namespace youklx {
    class Scene{
        public:
            #include"en/api/var.inl"
            #include"中文/接口/变量.inl"
        public:
            #include"en/api/function.inl"
            #include"中文/接口/函数.inl"
        private:
            #include"en/api/internal/var.inl"
            #include"en/api/internal/function.inl"
        public:
            ~Scene();
    };
    using 场景 = Scene;
}
#include"main.inl"
#include"en/remove.inl"
#include"中文/删除.inl"
#include"en/clear.inl"
#include"中文/清空.inl"
#include"en/pe_load.inl"
#include"en/load.inl"
#include"中文/加载.inl"