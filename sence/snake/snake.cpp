#include "vmode.cpp"

#include "sw/case1.cpp"
#include "sw/case2.cpp"
#include "sw/case3.cpp"
extern "C" EXPORT void snake() {
    int pt = 1;
    while (window.isrun) {
        window.run();
        draw.clear();
        if(scene.ptr != "snake") return;

        switch (pt) {
            case 1: splashScreenAnimation1(pt); break;
            case 2: splashScreenAnimation2(pt); break;
            case 3: splashScreenAnimation3(pt); break;
            default: break;
        }
        draw.vupdate();
        vulkan.updateTexture(image);
        vulkan.updateFontTexture(&font);
        vulkan.updateVertexBuffer(draw.vertex);
        vulkan.drawFrame(draw);
    }
}