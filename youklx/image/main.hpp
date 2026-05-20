#include "parameters/plpng.cpp"
#include "parameters/plimage.cpp"
namespace youklx {
    class Image {
        public:
            std::vector<std::vector<Plimage>> ima{};
        public:
            Image& lpng(const char* image);
    };
}
#include "lpng.cpp"