#include "vmode.inl"

extern "C" EXPORT void mainMenu() {

    配置文件.添加("json/mainMenu.json", "mainMenu");

    Gnik_luos::Line line1;
    Gnik_luos::Line line2;
    Gnik_luos::Line line3;
    line1.batch_load(配置文件.获取("mainMenu"), "line1");
    line2.batch_load(配置文件.获取("mainMenu"), "line2");
    line3.batch_load(配置文件.获取("mainMenu"), "line3");

    线程.绘制包([line1, line2, line3]() {
        窗口.drawer.line(line1);
        窗口.drawer.line(line2);
        窗口.drawer.line(line3);
    });

    运行.开始();
}
