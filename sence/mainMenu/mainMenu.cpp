#include "vmode.cpp"

extern "C" EXPORT void mainMenu() {
    int a{0},b{0};
    线程.更新包([&a](){a++;});
    线程.绘制包([&a](){std::println("a1={}",a);});
    线程.更新包([&b](){b++;});
    线程.绘制包([&b](){std::println("b1={}",b);});
    while(1) {
        线程.运行();
        if(a >= 3) break;
    }
    线程.包清理();
}