#include "vmain.inl"

int main() {
    try {
        youklx::init();
        youklx::窗口创建信息 wincinfo;
        wincinfo.初始化配置("ini/main.ini","wincinfo").加载();
        youklx::窗口信息 winsinfo;
        winsinfo.初始化配置("ini/main.ini","winsinfo").加载();
        窗口.配置(winsinfo).创建(wincinfo).调整位置();
        窗口.时间.初始化配置("ini/main.ini","time");
        场景.批量加载("ini/scene/main.ini","scene");
        场景.查询 = "mainMenu";
        {
            youklx::图片 临时图片;
            临时图片.加载(窗口.图标.c_str());
            窗口.设置图标(临时图片.ima[0][0]);
        }
        while(1) {
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
