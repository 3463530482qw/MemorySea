void splashScreenAnimation1(int &pt) {
    static float timer = 0.0f;
    float dt = window.time.different;
    if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;
    timer += dt;

    draw.image(image.ima[0][0], 0, 0, 1600, 900);

    float a = timer * 1.2f;
    if (a > 1.0f) a = 1.0f;

    draw.font(&font, "俄罗斯方块",
              560.0f, 280.0f, 90.0f, 0.0f, 0.0f, 0.0f,
              {0.3f, 0.7f, 1.0f, a});

    draw.font(&font, "← → 移动  ↑ 旋转  ↓ 加速",
              550.0f, 410.0f, 28.0f, 0.0f, 0.0f, 0.0f,
              {1.0f, 1.0f, 1.0f, a * 0.8f});

    draw.font(&font, "空格 硬降  ESC 返回",
              550.0f, 460.0f, 28.0f, 0.0f, 0.0f, 0.0f,
              {1.0f, 1.0f, 1.0f, a * 0.5f});

    if (timer > 2.0f) {
        timer = 0.0f;
        pt = 2;
    }
}