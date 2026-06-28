#include "parameters/plpng.cpp"
#include "parameters/plimage.cpp"
namespace youklx {
    class Image {
        public:
            std::vector<std::vector<Plimage>> ima{};    //图片数据
            // 纹理图集数据
            std::vector<unsigned char> atlasData;
            int atlasW{0}, atlasH{0};
            // 格式加载器注册表（类似 AI 的 act 字典，按扩展名分发）
            std::unordered_map<std::string, std::function<Plimage(const char*)>> loaders;
        public:
            Image& initLoaders();                        // 注册所有可用格式
            // 加载图片（根据扩展名自动选择加载器，强制 4 通道 RGBA）
            Image& load(const char* path);
            Image& load(const std::string& ini, const std::string& section);  
            Image& buildAtlas(); //将 ima 内所有图片拼接为图集
            Image& clean(); //清理加载的图片数据
            ~Image() { clean(); };
    };
}
#include "lpng.cpp"
#include "buildAtlas.cpp"
#include "clean.cpp"
