#include "parameters/plpng.cpp"
#include "parameters/plimage.cpp"
namespace youklx {
    class Image {
        public:
            std::vector<std::vector<Plimage>> ima{};    //图片数据
        public:
            Image& lpng(const char* image); //加载png图片 loda png         
            Image& ilpng(std::string ini, std::string ivrtp);  
            Image& clean(); //清理加载的图片数据
            ~Image() { clean(); };
    };
}
#include "lpng.cpp"
#include "clean.cpp"