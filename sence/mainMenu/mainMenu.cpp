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
        for (int i{0}; i < 100; i++)
        {
            draw.image(image.ima[0][0], 0, 0, 400, 400);
        }
        
        draw.line(0, 0, 1600, 100,
              15.0f, 0, 0, 0,
              {255, 0}, {0, 255}, {0, 255}, {1.0f, 1.0f});
              draw.image(image.ima[0][0], 0, 0, 200, 200,
              0.0f, 0.0f, 0.0f,
              {1.0f,1.0f,1.0f,1.0f}, {1.0f,1.0f,1.0f,1.0f},
              {1.0f,1.0f,1.0f,1.0f}, {1.0f,1.0f,1.0f,1.0f});

        // Draw → Vulkan 桥接
        draw.vupdate();
        vulkan.updateTexture(image.ima[0][0]);
        vulkan.updateVertexBuffer(draw.vertex);
        vulkan.drawFrame(draw);
    }
}