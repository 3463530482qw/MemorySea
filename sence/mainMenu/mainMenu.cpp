#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    // 线程测试
    int a{0},b{0};
    线程.更新包([&a](){

    });
    线程.绘制包([](){});
    while(窗口.是否运行) {
        //窗口.窗口火山.绘制帧(火山.device);
        线程.运行();
        窗口.运行();
    }
    线程.包清理();
}