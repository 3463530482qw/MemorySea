#include "parameters/plpng.cpp"
#include "parameters/plimage.cpp"
namespace youklx {
    class Image {
        public:
            std::vector<std::vector<Plimage>> ima{};    //图片数据
            // 纹理图集数据
            std::vector<unsigned char> atlasData;
            int atlasW{0}, atlasH{0};
        public:
            Image& lpng(const char* image); //加载png图片 loda png         
            Image& ilpng(std::string ini, std::string ivrtp);  
            Image& buildAtlas(); //将 ima 内所有图片拼接为图集
            Image& clean(); //清理加载的图片数据
            ~Image() { clean(); };
    };
}
#include "lpng.cpp"
#include "buildAtlas.cpp"
#include "clean.cpp"
