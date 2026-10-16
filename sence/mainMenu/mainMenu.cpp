#include "vmode.inl"

extern "C" EXPORT void mainMenu() {

    配置文件.添加("json/mainMenu/line.json", "mm_line");
    配置文件.添加("json/mainMenu/images.json", "mm_image");
    Gnik_luos::Line line1;
    Gnik_luos::Line line2;
    Gnik_luos::Line line3;
    Gnik_luos::Picture bk;
    bk.batch_load(配置文件.获取("mm_image"), "background");
    line1.batch_load(配置文件.获取("mm_line"), "line1");
    line2.batch_load(配置文件.获取("mm_line"), "line2");
    line3.batch_load(配置文件.获取("mm_line"), "line3");

    //字体归场景养:文字命令只按引用用它,字体对象必须活到场景跑完
    Gnik_luos::Font face;
    face.load("font/LXGWWenKaiLite-Light.ttf");
    Gnik_luos::Text hello;
    hello.font(face).text("你好世界").from(450.0f, 386.0f, 0.0f).size(64.0f).align("left").rgba(255, 255, 255, 1.0f);
    //没绑字体的那一条:改画库内默认字形贴图
    Gnik_luos::Text plain;
    plain.text("你好世界").from(950.0f, 386.0f, 0.0f).size(64.0f).align("left").rgba(255, 255, 255, 1.0f);
    (void)face;

    线程.绘制包([line1, line2, line3, bk, hello, plain]() {

        窗口.drawer.line(line1);
        窗口.drawer.line(line2);
        窗口.drawer.line(line3);
        窗口.drawer.picture(bk);
        窗口.drawer.text(hello);
        窗口.drawer.text(plain);
    });

    运行.开始();
}
