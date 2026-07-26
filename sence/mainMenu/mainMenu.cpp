#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    // 线程测试
    int a{0},b{0};
    线程.更新包([&a](){
        
    });
    线程.绘制包([](){});
    while(窗口.是否运行) {
        线程.运行();
        窗口.运行();
        
        // 检测任意按键
        for (int vk = 0x08; vk <= 0xFE; ++vk) {
            if (窗口.key.press(vk)) {
                std::println("{}",vk);
            }
        }
        std::println("鼠标位置: ({:.1f}, {:.1f})", 窗口.mouse.x, 窗口.mouse.y);
        
    }
    线程.包清理();
}