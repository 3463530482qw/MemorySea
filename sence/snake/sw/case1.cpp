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

        draw.font(youklx::Fontcmd{&font, "贪吃蛇"}.sp(665.0f, 300.0f).ss(90.0f).srgba({0.2f, 1.0f, 0.3f, a}));

        draw.font(youklx::Fontcmd{&font, "← → ↑ ↓ 控制方向"}.sp(660.0f, 430.0f).ss(28.0f).srgba({1.0f, 1.0f, 1.0f, a * 0.8f}));

        draw.font(youklx::Fontcmd{&font, "ESC 返回"}.sp(725.0f, 480.0f).ss(28.0f).srgba({1.0f, 1.0f, 1.0f, a * 0.5f}));
    });

    if (timer > 2.0f) {
        timer = 0.0f;
        pt = 2;
    }
}