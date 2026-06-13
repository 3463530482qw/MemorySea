void splashScreenAnimation1(int &pt) {
    // ---- 数据 ----
    static constexpr int    CNT = 5;
    static constexpr float  OH  = 120.0f, GAP = 30.0f, STEP = OH + GAP;
    static constexpr float  NW  = 1400.0f, FW = 1600.0f;
    static constexpr float  VTOP = 180.0f, VBOT = 900.0f;
    static constexpr float  MAX_SCROLL_BASE = CNT * STEP - (VBOT - VTOP);
    static constexpr float  NX  = (1600.0f - NW) * 0.5f;

    static float posY[CNT]{};
    static float scroll = 0.0f;
    static float scrollVel = 0.0f;
    static bool  inited = false;

    static youklx::Imagecmd bk = {
        .img = image.ima[0][0],
        .x = 0,
        .y = 0,
        .w = 1600,
        .h = 900
    };

    // ---- 初始化 ----
    if (!inited) {
        for (int i = 0; i < CNT; i++) posY[i] = 5000.0f;
        inited = true;
    }

    static int focus = -1;

    thread.wth_update([&]() {
        // ---- 弹性滚动 ----
        float dt = window.time.different;
        scroll -= window.mouse.wheelY * 40.0f;
        float maxScroll = MAX_SCROLL_BASE < 0.0f ? 0.0f : MAX_SCROLL_BASE;

        // 超出边界时施加弹性恢复力
        if (scroll < 0.0f) {
            scrollVel += (-scroll) * 12.0f * dt;
        } else if (scroll > maxScroll) {
            scrollVel += (maxScroll - scroll) * 12.0f * dt;
        }
        scroll += scrollVel * dt;
        scrollVel *= std::exp(-12.0f * dt);
        if (scrollVel * scrollVel < 0.01f) scrollVel = 0.0f;

        // 无弹性力时做硬夹紧
        if (scrollVel == 0.0f) {
            if (maxScroll <= 0.0f) scroll = 0.0f;
            else scroll = std::clamp(scroll, 0.0f, maxScroll);
        }

        // ---- 位置复原动画 ----
        for (int i = 0; i < CNT; i++) {
            float target = VTOP + i * STEP;
            posY[i] += (target - posY[i]) * dt * 10.0f;
        }

        // ---- 焦点检测 ----
        focus = -1;
        for (int i = CNT - 1; i >= 0; i--) {
            float dy = posY[i] - scroll;
            if (window.mouse.x >= NX && window.mouse.x <= NX + NW &&
                window.mouse.y >= dy && window.mouse.y <= dy + OH) {
                focus = i;
                break;
            }
        }
    });

    thread.wth_draw([&]() {
        draw.image(bk);
        for (int i = 0; i < CNT; i++) {
            float dy = posY[i] - scroll;
            if (dy + OH < 0.0f || dy > 900.0f) continue;

            // 先绘制选项本体
            draw.image(youklx::Imagecmd{image.ima[0][4], NX, dy, NW, OH});

            // 焦点效果叠加在选项之上
            if (i == focus) {
                float fx = (1600.0f - FW) * 0.5f;
                draw.image(youklx::Imagecmd{image.ima[0][5], fx, dy, FW, OH});
            }

            // 左侧绘制编号
            draw.font(youklx::Fontcmd{&font, std::to_string(i + 1),
                      NX - 100.0f, dy + 25.0f, OH, 0.0f, 0.0f, 0.0f,
                      {1.0f, 1.0f, 1.0f, 1.0f}});
            if (i == 0) {
                draw.font(youklx::Fontcmd{&font, "俄罗斯方块",
                      NX + 450.0f, dy + 15.0f, OH, 0.0f, 0.0f, 0.0f,
                      {1.0f, 1.0f, 1.0f, 1.0f}});
            } else if (i == 1) {
                draw.font(youklx::Fontcmd{&font, "贪吃蛇",
                      NX + 550.0f, dy + 15.0f, OH, 0.0f, 0.0f, 0.0f,
                      {1.0f, 1.0f, 1.0f, 1.0f}});
            } else if (i == 2) {
                draw.font(youklx::Fontcmd{&font, "数独",
                      NX + 600.0f, dy + 15.0f, OH, 0.0f, 0.0f, 0.0f,
                      {1.0f, 1.0f, 1.0f, 1.0f}});
            } else if (i == 3) {
                draw.font(youklx::Fontcmd{&font, "平台跳跃",
                      NX + 500.0f, dy + 15.0f, OH, 0.0f, 0.0f, 0.0f,
                      {1.0f, 1.0f, 1.0f, 1.0f}});
            } else {
                draw.font(youklx::Fontcmd{&font, "待完成",
                      NX + 550.0f, dy + 15.0f, OH, 0.0f, 0.0f, 0.0f,
                      {1.0f, 1.0f, 1.0f, 1.0f}});
            }
        }

        draw.image(youklx::Imagecmd{image.ima[0][6], 0, 0, 1600, 900});
    });

    // ---- 点击判断 ----
    if (window.mouse.leftPressed() && focus >= 0) {
        if(focus == 0){
            scene.ptr = "tetris";
        }
        if(focus == 1){
            scene.ptr = "snake";
        }
        if(focus == 2){
            scene.ptr = "sudoku";
        }
        if(focus == 3){
            scene.ptr = "jump";
        }
    }
}