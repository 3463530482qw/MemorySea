void splashScreenAnimation3(int &pt) {
    static float timer = 0.0f;

    thread.wth_update([&]() {
        float dt = window.time.different;
        if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;
        timer += dt;
    });

    thread.wth_draw([&]() {
        draw.image(youklx::Imagecmd{image.ima[0][0], 0.0f, 0.0f, 1600.0f, 900.0f});

        float a = timer * 0.8f;
        if (a > 1.0f) a = 1.0f;

        draw.font(youklx::Fontcmd{&font, "游戏结束",
                  656.0f, 300.0f, 72.0f, 0.0f, 0.0f, 0.0f,
                  {1.0f, 0.85f, 0.2f, a}});
    });

    if (timer > 1.5f || window.keyboard.anyPressed() || window.mouse.leftPressed()) {
        timer = 0.0f;
        scene.ptr = "mselect";
    }
}