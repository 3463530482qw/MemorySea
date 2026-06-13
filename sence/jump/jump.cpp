#include "vmode.cpp"

#include "sw/case1.cpp"
#include "sw/case2.cpp"
#include "sw/case3.cpp"
extern "C" EXPORT void jump() {
    int pt = 1;
    while (window.isrun) {
        if(scene.ptr != "jump") return;
        window.run();

        switch (pt) {
            case 1: splashScreenAnimation1(pt); break;
            case 2: splashScreenAnimation2(pt); break;
            case 3: splashScreenAnimation3(pt); break;
            default: break;
        }
    }
}
