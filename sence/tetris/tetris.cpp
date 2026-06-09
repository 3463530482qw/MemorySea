#include "vmode.cpp"

#include "sw/case1.cpp"
#include "sw/case2.cpp"
#include "sw/case3.cpp"
extern "C" EXPORT void tetris() {
    int pt = 1;
    while (window.isrun) {
        if(scene.ptr != "tetris") return;
        window.run();

        switch (pt) {
            case 1: splashScreenAnimation1(pt); break;
            case 2: splashScreenAnimation2(pt); break;
            case 3: splashScreenAnimation3(pt); break;
            default: break;
        }
    }
}