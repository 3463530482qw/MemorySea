#include "vmain.inl"

int main() {
    try {
        youklx::init();
        {
            youklx::窗口创建信息 wincinfo;
            wincinfo.初始化配置("ini/main.ini","wincinfo").加载();
            youklx::窗口信息 winsinfo;
            winsinfo.初始化配置("ini/main.ini","winsinfo").加载();
            窗口.配置(winsinfo).创建(wincinfo).调整位置();
            窗口.时间.初始化配置("ini/main.ini","time");

            场景.批量加载("ini/scene/main.ini","scene");
            场景.查询 = "mainMenu";
            
            youklx::图片 临时图片;
            临时图片.加载(窗口.图标.c_str());
            窗口.设置图标(临时图片.ima[0][0]);

            youklx::火山初始化信息 itvinfo;
            itvinfo.窗口名 = 窗口.名称;
            火山.初始化(itvinfo);

            窗口.窗口火山.创建表面(窗口.id, 火山.instance);
            窗口.窗口火山.查找图形队列族(火山.physicalDevice);
            火山.创建逻辑设备(窗口.窗口火山.图形队列族索引);
            窗口.窗口火山.创建交换链(火山.physicalDevice, 火山.device, 窗口.w, 窗口.h);
            窗口.窗口火山.创建图像视图(火山.device);
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
