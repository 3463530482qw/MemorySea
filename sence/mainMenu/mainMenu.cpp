#include "vmode.inl"
#include "slot/main.hpp"

extern "C" EXPORT void mainMenu() {
    Gnik_luos::槽位 槽位;
    配置文件.添加("json/mainMenu/slot.json", "主菜单资源");
    槽位.装载(图片, 配置文件.获取("主菜单资源"));
    运行.开始();
}
