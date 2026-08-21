#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    int a{0};
    线程.update_pack([&a](){
        a++;
    });
    线程.draw_pack([&a](){
        std::println("输出a的值是:{}", a);
    });
    运行.start();
}
