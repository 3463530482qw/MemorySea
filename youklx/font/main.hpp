#include "en/parameters/glyph.inl"
namespace youklx {
    class Font {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/var.inl"
        private:
            #include "en/api/internal/function.inl"
    };
    using 字体 = Font;
}
#include "en/load.inl"
#include "en/px.inl"
#include "en/pad.inl"
#include "en/bake.inl"
#include "en/rebuild.inl"
#include "en/query.inl"
#include "en/bindrenderer.inl"
#include "en/recreatetexture.inl"
#include "en/uploadatlas.inl"
