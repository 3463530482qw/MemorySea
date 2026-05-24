#include "vmode.cpp"


extern "C" EXPORT void mainMenu() {
    while (window.isrun) {
        window.run();
    }
    std::cout << Scene.ptr << std::endl;
}
