#include "vmain.inl"

int main() {
    try {
        Gnik_luos::initialize();
        {
            配置文件.添加("json/main.json", "初始化配置");
            场景.批量加载(配置文件.获取("初始化配置"),"scene");
            场景.当前场景 = "mainMenu";
            场景.目标场景 = 场景.当前场景;

            Gnik_luos::窗口配置信息 窗口配置信息;
            窗口配置信息.批量加载(配置文件.获取("初始化配置"),"window_info");
            窗口.设置(窗口配置信息);

            Gnik_luos::窗口创建信息 窗口创建信息;
            窗口创建信息.批量加载(配置文件.获取("初始化配置"),"window_create_info");
            窗口.创建(窗口创建信息);
            窗口.time.batch_load(配置文件.获取("初始化配置"),"window_time");

            Gnik_luos::图片 临时图片;
            临时图片.load(窗口.icon.c_str());
            窗口.set_icon(临时图片.pack[0][0]);

            运行.指定场景(场景);
            运行.指定线程(线程);
            运行.specify_window(窗口);
        }
        while(窗口.isrun) {
            if (auto it = 场景.数据.find(场景.目标场景); it != 场景.数据.end()) {
                it->second();
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "异常: " << e.what() << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
