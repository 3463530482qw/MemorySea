namespace youklx {
    class FontRender {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
    };
    using 字体渲染 = FontRender;
}
#include "en/findmemorytype.inl"
#include "en/recreatetexture.inl"
#include "en/createtexture.inl"
#include "en/createpipeline.inl"
#include "en/createvertexbuffer.inl"
#include "en/init.inl"
#include "en/draw.inl"
