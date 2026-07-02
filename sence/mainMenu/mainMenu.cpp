#include "vmode.cpp"


extern "C" EXPORT void mainMenu() {
    while (window.isrun) {
        if(scene.ptr != "mainMenu") return;
        window.run();
        std::println("{}",window.time.current);
    }
}