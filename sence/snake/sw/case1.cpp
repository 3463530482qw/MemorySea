void splashScreenAnimation1(int &pt) {
    static float timer = 0.0f;
    float dt = window.time.different;
    if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;
    timer += dt;

    draw.image(image.ima[0][0], 0, 0, 1600, 900);

    float a = timer * 1.2f;
    if (a > 1.0f) a = 1.0f;

    draw.font(&font, "贪吃蛇",
              665.0f, 300.0f, 90.0f, 0.0f, 0.0f, 0.0f,
              {0.2f, 1.0f, 0.3f, a});

    draw.font(&font, "← → ↑ ↓ 控制方向",
              660.0f, 430.0f, 28.0f, 0.0f, 0.0f, 0.0f,
              {1.0f, 1.0f, 1.0f, a * 0.8f});

    draw.font(&font, "ESC 返回",
              725.0f, 480.0f, 28.0f, 0.0f, 0.0f, 0.0f,
              {1.0f, 1.0f, 1.0f, a * 0.5f});

    if (timer > 2.0f) {
        timer = 0.0f;
        pt = 2;
    }
}