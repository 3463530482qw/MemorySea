#include "vmode.cpp"

#include "sw/case1.cpp"
extern "C" EXPORT void mselect() {  
    int pt = 1;
    while (window.isrun) {
        if(scene.ptr != "mselect") return;
        window.run();

        switch (pt) {
            case 1: splashScreenAnimation1(pt); break;
            default: break;
        }
    }
}