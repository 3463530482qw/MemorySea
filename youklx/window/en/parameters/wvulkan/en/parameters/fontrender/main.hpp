#include "en/parameters/pushconsts.inl"
namespace youklx {
    class FontRender {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
    };
    using 字体渲染 = FontRender;
}
#include "en/init.inl"
#include "en/createdescriptors.inl"
#include "en/createpipeline.inl"
#include "en/createvertexbuffer.inl"
#include "en/draw.inl"
