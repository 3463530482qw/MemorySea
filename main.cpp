#include "vmain.inl"

int main() {
    try {
        Gnik_luos::initialize();
        {
            配置文件.添加("json/main.json", "初始化配置");
            场景.批量加载(配置文件.获取("初始化配置"),"scene");
            场景.当前场景 = "mainMenu";
        }
        while(1) {
            if (auto it = 场景.数据.find(场景.当前场景); it != 场景.数据.end()) {
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
