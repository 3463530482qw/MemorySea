#include "vmain.inl"

int main() {
    try {
        luos::initialize();
        {
            配置文件.添加("ini/main.ini", "初始化配置");
            youklx::窗口创建信息 wincinfo;
            wincinfo.初始化配置(配置文件.取("初始化配置"),"wincinfo").加载();
            youklx::窗口信息 winsinfo;
            winsinfo.初始化配置(配置文件.取("初始化配置"),"winsinfo").加载();
            窗口.配置(winsinfo).创建(wincinfo).调整位置();
            窗口.时间.初始化配置(配置文件.取("初始化配置"),"time");

            场景.批量加载("ini/scene/main.ini","scene");
            场景.查询 = "mainMenu";

            youklx::图片 临时图片;
            临时图片.加载(窗口.图标.c_str());
            窗口.设置图标(临时图片.ima[0][0]);

            youklx::火山初始化信息 itvinfo;
            itvinfo.窗口名 = 窗口.名称;
            火山.初始化(itvinfo);
            窗口.窗口火山.init(火山);
        }
        while(窗口.是否运行) {

            if (auto it = 场景.菜单.find(场景.查询); it != 场景.菜单.end()) {
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
