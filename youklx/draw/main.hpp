#include "../font/main.hpp"
#include "parameters/linecmd.cpp"
#include "parameters/imagecmd.cpp"
#include "parameters/fontcmd.cpp"
#include "parameters/drawcmd.cpp"
namespace youklx {
    class Draw {
        public:
            int stsizew{0}; // 逻辑大小宽度
            int stsizeh{0}; // 逻辑大小高度

            unsigned int nuth{0}; //线程数
            std::vector<std::thread> sth; //线程

            std::vector<Drawcmd> commands; // 绘制命令
            int cptr{0}; // 命令指针
            std::vector<float> vertex; // 顶点数据
            std::vector<int> vertexptr; // 顶点指针

            int nt;      //模块指针
            int mod;     //模块大小
            int emod;    //结尾模块大小
        public:
            Draw();
            Draw& lstsize(int w, int h); // 设置逻辑大小
            Draw& ilstsize(std::string ini, std::string ivrtp, std::string witp, std::string hitp);
            Draw& line(
                int x1, int y1, int x2, int y2,
                float thickness,
                int rotate, int rox, int roy,
                std::array<int,2> r, std::array<int,2> g,
                std::array<int,2> b, std::array<float,2> a
            ); // 绘制直线
            Draw& image(
                Plimage img,
                float x, float y,
                float w, float h,
                float rotate = 0.0f, float rox = 0.0f, float roy = 0.0f,
                std::array<float,4> c1 = {1.0f,1.0f,1.0f,1.0f}, 
                std::array<float,4> c2 = {1.0f,1.0f,1.0f,1.0f},
                std::array<float,4> c3 = {1.0f,1.0f,1.0f,1.0f}, 
                std::array<float,4> c4 = {1.0f,1.0f,1.0f,1.0f}
            ); // 绘制图片
            Draw& font(
                Font* font,
                std::string text,
                float x, float y,
                float fontSize,
                float rotate = 0.0f, float rox = 0.0f, float roy = 0.0f,
                std::array<float,4> rgba = {1.0f,1.0f,1.0f,1.0f}
            ); // 绘制文字
            Draw& clear();   // 清空绘制命令
            Draw& vupdate(); // 更新顶点数据
            
    };
}

#include "draw.cpp"
#include "lstsize.cpp"
#include "line.cpp"
#include "image.cpp"
#include "font.cpp"
#include "calculate/line.cpp"
#include "calculate/image.cpp"
#include "calculate/font.cpp"
#include "vupdate.cpp"
