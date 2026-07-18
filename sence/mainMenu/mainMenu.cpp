#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    // 创建两个测试窗口
    有棵黎夕的::窗口 win1, win2;

    youklx::windowsinfo info1;
    info1.name = "Window One";

    youklx::windowsinfo info2;
    info2.name = "Window Two";
    info2.w = 400;
    info2.h = 300;

    win1.reinfo(info1);
    win2.reinfo(info2);
    win1.create();
    win2.create();

    // 线程测试
    int a{0},b{0};
    线程.更新包([&a](){a++;});
    线程.绘制包([&a](){std::println("a1={}",a);});
    线程.更新包([&b](){b++;});
    线程.绘制包([&b](){std::println("b1={}",b);});
    while(1) {
        线程.运行();
    }
    线程.包清理();
}