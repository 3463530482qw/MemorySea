#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    // 线程测试
    int a{0},b{0};
    youklx::窗口 窗口1;
    窗口1.配置().创建();
    线程.更新包([&窗口1](){
        if(窗口1.是否运行) {
            窗口1.运行();
            std::println("{}",窗口1.是否运行);
        }
    });
    线程.绘制包([](){});
    while(窗口.是否运行) {
        线程.运行();
        窗口.运行();
    }
    线程.包清理();
}