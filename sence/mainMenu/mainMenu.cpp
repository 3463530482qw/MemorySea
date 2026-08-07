#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    // 字体:用窗口绑定的字体(渲染管线从此字体取图集)
    static bool fontLoaded = []() {
        窗口.字体.加载("font/LXGWWenKaiLite-Light.ttf");
        return true;
    }();
    (void)fontLoaded;

    // 线程测试
    int a{0},b{0};
    线程.更新包([&a](){
        窗口.绘制.font(youklx::字体绘制命令().sf(&窗口.字体).sc("你好").sp(100, 200).ss(32).srgba({1, 0, 0, 1}));
    });
    线程.更新包([&a](){
        窗口.绘制.font(youklx::字体绘制命令().sf(&窗口.字体).sc("世界").sp(100, 250).ss(48).srgba({0, 1, 0, 1}));
    });
    线程.绘制包([](){});
    while(窗口.是否运行) {
        线程.运行();
        窗口.运行();
    }
    线程.包清理();
}
