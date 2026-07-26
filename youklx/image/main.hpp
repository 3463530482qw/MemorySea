#include "en/parameters/plimage.inl"
namespace youklx {
    class Image {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
    };
    using 图片 = Image;
}
#include "en/load.inl"