#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    // 相机竖起来:从画布平面里立到地面之上(y 向下,所以"地面之上"是 y 负),朝向基本水平、略微低头,
    // 于是地面从画面下方一路铺到远处的地平线 —— 与引擎编辑器的默认视角同一个意思。
    // 地面只在透视档看得见 —— 正交档是 2D 档(世界 xy 就是画布像素),地面躺在 xz 平面上、对着屏幕只有一条边。
    窗口.camera.is_perspective = true;
    窗口.camera.x = 640.0f;
    窗口.camera.y = -600.0f;
    窗口.camera.z = 1200.0f;
    窗口.camera.rotation_x = 20.0f;
    窗口.camera.rotation_y = 0.0f;
    窗口.camera.rotation_z = 0.0f;
    窗口.camera.fov = 60.0f;
    窗口.camera.near_plane = 1.0f;
    窗口.camera.far_plane = 20000.0f;

    线程.绘制包([&]() {
    });

    运行.开始();
}
