#include "vmain.cpp"

int main() {
    try {
        youklx::init();

        scene.ldlli("ini/scene/main.ini","scene");
        scene.ptr = "mainMenu";
        while(1) {
            if (auto it = scene.dict.find(scene.ptr); it != scene.dict.end()) {
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
