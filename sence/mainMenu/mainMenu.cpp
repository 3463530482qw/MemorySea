#include "vmode.inl"

extern "C" EXPORT void mainMenu() {
    Gnik_luos::Draw draw;
    Gnik_luos::Draw_line_cmd line;
    Gnik_luos::Camera camera;

    const float w = static_cast<float>(窗口.logic_width);
    const float h = static_cast<float>(窗口.logic_height);
    camera.x = w * 0.5f;              // 相机对准逻辑画布中心,外部填充按它看到的范围铺
    camera.y = h * 0.5f;
    camera.canvas_width = w;
    camera.canvas_height = h;

    draw.bind_window(窗口);
    draw.bind_camera(camera);

    line.line_width(6.0f)
        .from(w * 0.125f, h * 0.5f)
        .to(w * 0.875f, h * 0.5f)
        .to(w * 0.875f, h * 0.1f)
        //.to(w * 0.125f, h * 0.5f)
        //.to(w * 0.175f, h * 0.8f)
        //.to(w * 0.175f, h * 0.5f)
        .edge_both(16.0f);
        //.end()
        //.fill_above()
        //.pixelate(8.0f) 
        //.fill_inside(255, 125, 0, 1.0f)
        

    线程.绘制包([&]() {
        const float t = 0.5f + 0.5f * std::sin(static_cast<float>(窗口.time.current) * 0.8f);
        line.color(static_cast<uint8_t>(255.0f * t), 120, static_cast<uint8_t>(255.0f * (1.0f - t)));
        draw.draw(line);
    });

    运行.开始();
}
