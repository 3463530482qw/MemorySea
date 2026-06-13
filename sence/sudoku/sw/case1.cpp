void splashScreenAnimation1(int &pt) {
    static float timer = 0.0f;

    thread.wth_update([&]() {
        float dt = window.time.different;
        if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;
        timer += dt;
    });

    thread.wth_draw([&]() {
        draw.image(youklx::Imagecmd{image.ima[0][0], 0.0f, 0.0f, 1600.0f, 900.0f});

        float a = timer * 1.2f;
        if (a > 1.0f) a = 1.0f;

        draw.font(youklx::Fontcmd{&font, "数独",
                  710.0f, 300.0f, 90.0f, 0.0f, 0.0f, 0.0f,
                  {0.4f, 0.6f, 1.0f, a}});

        draw.font(youklx::Fontcmd{&font, "点击格子选中  |  1-9 填入数字  |  ESC 返回",
                  530.0f, 450.0f, 28.0f, 0.0f, 0.0f, 0.0f,
                  {1.0f, 1.0f, 1.0f, a * 0.8f}});
    });

    if (timer > 2.0f) {
        timer = 0.0f;
        pt = 2;
    }
}