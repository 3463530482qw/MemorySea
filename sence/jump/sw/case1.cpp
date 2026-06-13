void splashScreenAnimation1(int &pt) {
    static float timer = 0.0f;

    thread.wth_update([&]() {
        float dt = window.time.different;
        if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;
        timer += dt;
    });

    thread.wth_draw([&]() {
        draw.image(youklx::Imagecmd{image.ima[0][0], 0, 0, 1600, 900});

        float a = timer * 1.2f;
        if (a > 1.0f) a = 1.0f;

        draw.font(youklx::Fontcmd{&font, "平台跳跃",
                  620.0f, 280.0f, 90.0f, 0.0f, 0.0f, 0.0f,
                  {0.3f, 0.8f, 1.0f, a}});

        draw.font(youklx::Fontcmd{&font, "A D 移动  SPACE 跳跃",
                  620.0f, 420.0f, 30.0f, 0.0f, 0.0f, 0.0f,
                  {1.0f, 1.0f, 1.0f, a * 0.8f}});

        draw.font(youklx::Fontcmd{&font, "触水或左墙即失败  每秒+1分",
                  610.0f, 470.0f, 28.0f, 0.0f, 0.0f, 0.0f,
                  {1.0f, 0.85f, 0.5f, a * 0.7f}});

        draw.font(youklx::Fontcmd{&font, "ESC 返回",
                  720.0f, 540.0f, 28.0f, 0.0f, 0.0f, 0.0f,
                  {1.0f, 1.0f, 1.0f, a * 0.5f}});
    });

    if (timer > 2.5f) {
        timer = 0.0f;
        pt = 2;
    }
}
