#include "vmode.cpp"
extern "C" EXPORT void mainMenu() {
    float x = 0.0f;
    while (window.isrun) {
        if(x > 1.0f) {
            x = 0.0f;
        } else {
            x += 0.01f;
        }
        window.run();

        // 每帧清空并重新设置绘制命令
        draw.clear();
        draw.line(0, 0, 1600, 100,
              25.0f, 0, 0, 0,
              {255, 0}, {0, 255}, {0, 255}, {1.0f, 0});

        // Draw → Vulkan 桥接：生成顶点并上传
        draw.vupdate();
        vulkan.updateVertexBuffer(draw.vertex);
        vulkan.drawFrame();
    }
}