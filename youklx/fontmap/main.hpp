namespace youklx {
    class Fontmap {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 字体仓库 = Fontmap;
}
#include "en/load.inl"
#include "en/iload.inl"
