#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    int a{0};     
    线程.更新包([&a](){
        a++;
    });
    线程.绘制包([&a](){
        std::println("第{}次输出值是:{}", 窗口.mouse.y, 窗口.mouse.x);
    });
    运行.开始();
}
