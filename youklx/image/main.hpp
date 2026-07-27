#include "en/parameters/plimage.inl"
namespace youklx {
    class Image {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/function.inl"
        public:
            ~Image() { clear(); };
    };
    using 图片 = Image;
}
#include "en/load.inl"
#include "en/clear.inl"