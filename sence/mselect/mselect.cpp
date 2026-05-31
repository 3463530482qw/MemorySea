#include "vmode.cpp"

extern "C" EXPORT void mselect() {  
    while (window.isrun) {
        window.run();
        draw.clear();
        

        draw.vupdate();
        vulkan.updateTexture(image);
        vulkan.updateFontTexture(&font);
        vulkan.updateVertexBuffer(draw.vertex);
        vulkan.drawFrame(draw);
    }
}