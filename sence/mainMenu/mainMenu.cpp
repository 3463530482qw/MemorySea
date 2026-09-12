#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    int a{0};     
    线程.更新包([&a](){
        a++;
    });
    线程.绘制包([&a](){
        if(窗口.key.press(Gnik_luos::yk_a)) {
            std::println("输出了a");
        }
        std::println("第{}次输出值是:{}", a, 窗口.time.current);
    });
    运行.开始();
}
