#include "vmain.inl"

int main() {
    try {
        Gnik_luos::initialize();
        {
            配置文件.add("json/main.json", "初始化配置");
            场景.batch_load(配置文件.get("初始化配置"),"scene");
            场景.current_scene = "mainMenu";
        }
        while(1) {
            if (auto it = 场景.data.find(场景.current_scene); it != 场景.data.end()) {
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
