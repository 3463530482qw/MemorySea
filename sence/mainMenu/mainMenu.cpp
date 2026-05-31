#include "vmode.cpp"

#include "sw/case1.cpp"
#include "sw/case2.cpp"
#include "sw/case3.cpp"
extern "C" EXPORT void mainMenu() {
    std::array<int, 161> lx; 
    std::array<int, 161> ly; 
    int pt = 1;
    while (window.isrun) {
        if(scene.ptr != "mainMenu") return;
        window.run();
        draw.clear();
        switch (pt) {
            case 1: splashScreenAnimation1(pt); break;
            case 2: splashScreenAnimation2(pt,lx,ly); break;
            case 3: splashScreenAnimation3(pt,lx,ly); break;
            default: break;
        }

        draw.vupdate();
        vulkan.updateTexture(image);
        vulkan.updateFontTexture(&font);
        vulkan.updateVertexBuffer(draw.vertex);
        vulkan.drawFrame(draw);
    }
}
