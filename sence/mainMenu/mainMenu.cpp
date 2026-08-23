#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    int a{0};
    线程.更新包([&a](){
        a++;
    });
    线程.绘制包([&a](){
        //std::println("输出a的值是:{}", a);
    });
    运行.开始();
}
