#include "vmain.cpp"

int main() {
    try {
        youklx::init();

        场景.iload("ini/scene/main.ini","scene");
        场景.查询 = "mainMenu";
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
