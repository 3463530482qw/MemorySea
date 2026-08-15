#include "en/parameters/vertex.inl"
#include "en/parameters/batch.inl"
#include "en/font/fontblock.inl"
#include "en/parameters/font/main.hpp"
namespace youklx {
    class Draw {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/function.inl"
    };
    using 绘制 = Draw;
}
#include "en/font/utf8next.inl"
#include "en/font/fontblocks.inl"
#include "en/font/fontemit.inl"
#include "en/font/font.inl"
#include "en/clear.inl"
