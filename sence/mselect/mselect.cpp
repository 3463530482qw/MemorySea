#include "vmode.cpp"

#include "sw/case1.cpp"
extern "C" EXPORT void mselect() {  
    int pt = 1;
    while (window.isrun) {
        window.run();
        draw.clear();
        if(scene.ptr != "mselect") return;

        switch (pt) {
            case 1: splashScreenAnimation1(pt); break;
            default: break;
        }
        draw.vupdate();
        vulkan.updateTexture(image);
        vulkan.updateFontTexture(&font);
        vulkan.updateVertexBuffer(draw.vertex);
        vulkan.drawFrame(draw);
    }
}
