#include "parameters/linecmd.cpp"
#include "parameters/imagecmd.cpp"
#include "parameters/fontcmd.cpp"
#include "parameters/drawcmd.cpp"
namespace youklx {
    class Draw {
        public:
            int stsizew{0}; // 逻辑大小宽度
            int stsizeh{0}; // 逻辑大小高度

            std::vector<Drawcmd> commands; // 绘制命令
            int cptr{0}; // 命令指针
            std::vector<float> vertex; // 顶点数据
            std::vector<int> vertexptr; // 顶点指针
        public:
            Draw();
            Draw& lstsize(int w, int h); // 设置逻辑大小
            Draw& ilstsize(std::string ini, std::string ivrtp, std::string witp, std::string hitp);
            Draw& line(
                Linecmd &cmd
            ); // 绘制直线（传入完整 Linecmd）
            Draw& lineBegin(int x, int y); // 创建新折线，设置起始顶点
            Draw& lineTo(int x, int y);    // 为当前折线追加顶点
            Draw& color(int r, int g, int b, float a = 1.0f);  // 设置画笔色（后续 lineTo 使用此色）
            Draw& image(
                const Imagecmd &cmd
            ); // 绘制图片
            Draw& font(Fontcmd cmd); // 绘制文字
            Draw& clear();   // 清空绘制命令
            Draw& vupdate(); // 更新顶点数据
            
    };
}

#include "draw.cpp"
#include "lstsize.cpp"
// std::visit 辅助：用 lambda 集合访问 variant
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
#include "line.cpp"
#include "image.cpp"
#include "font.cpp"
#include "calculate/line.cpp"
#include "calculate/image.cpp"
#include "calculate/font.cpp"
#include "vupdate.cpp"
