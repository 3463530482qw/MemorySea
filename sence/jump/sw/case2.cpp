void splashScreenAnimation2(int &pt) {
    // ---- 常量 ----
    static constexpr float PLYR_SZ   = 30.0f;
    static constexpr float PLYR_HALF = 15.0f;
    static constexpr float GRAVITY   = 650.0f;
    static constexpr float JUMP_VEL  = -420.0f;
    static constexpr float PLYR_SPD  = 280.0f;
    static constexpr float PLAT_SPD_START  = 80.0f;
    static constexpr float PLAT_SPD_MAX    = 300.0f;
    static constexpr float PLAT_SPD_RAMP   = 0.73f;
    static constexpr float WATR_LVL  = 820.0f;
    static constexpr float SCRN_W    = 1600.0f;
    static constexpr float SCRN_H    = 900.0f;

    static constexpr float SPRING_K     = 0.12f;
    static constexpr float SPRING_DAMP  = 0.40f;
    static constexpr int   MAX_BOUNCES  = 2;

    // ---- 平台 ----
    struct Platform { float x, y, w, thick; };
    static std::vector<Platform> plats;

    // ---- 主角 ----
    static float px = 800.0f, py = 500.0f;
    static float vx = 0.0f, vy = 0.0f;
    static bool  onGround = false;
    static int   bounceCount = 0;
    static float platSpd = PLAT_SPD_START;

    // ---- 状态 ----
    static float spawnTimer = 0.0f;
    static float nextSpawn  = 1.2f;
    static float scoreTimer = 0.0f;
    static int   score      = 0;
    static bool  dead       = false;
    static bool  inited     = false;
    static float gameTime   = 0.0f;

    // ---- 水波 ----
    static constexpr int   WN   = 80;
    static constexpr float WDX  = 1600.0f / 80.0f;
    static float wy[WN];
    static float wyv[WN];
    static float wyBase = 835.0f;
    static float wavePhase = 0.0f;
    static constexpr float WAVE_SPEED = 1.5f;
    static constexpr float WAVE_AMP   = 15.0f;
    static constexpr float WAVE_FREQ  = 0.015f;
    static constexpr float CLOSE_DIST = 160.0f;

    // ---- 飞溅粒子 ----
    static constexpr int MAX_SPLASH = 40;
    struct Splash { float x, y, vx, vy, life; };
    static std::vector<Splash> splashes;

    // ---- 绘制命令模板 ----
    static youklx::Linecmd platCmd;
    static youklx::Linecmd plyrCmd;
    static youklx::Linecmd waterCmd;
    static youklx::Linecmd splashCmd;

    thread.wth_update([&]() {
        float dt = window.time.different;

        if (!inited) {
            plats.clear();
            splashes.clear();
            plats.push_back({1450.0f, 550.0f, 300.0f, 14.0f});
            px = 1520.0f; py = 550.0f - PLYR_HALF;
            vx = vy = 0.0f;
            onGround = true; dead = false; bounceCount = 0;
            spawnTimer = 0.0f; nextSpawn = 1.2f;
            scoreTimer = 0.0f; score = 0;
            gameTime = 0.0f; platSpd = PLAT_SPD_START;
            for (int i = 0; i < WN; i++) {
                wy[i]  = wyBase;
                wyv[i] = 0.0f;
            }
            // 模板命令初始样式（仅首次）
        platCmd.color(160, 190, 190, 1.0f);
        plyrCmd.color(50, 230, 80, 1.0f);
        waterCmd.color(180, 210, 235, 0.80f);
        splashCmd.color(200, 220, 255, 0.9f);
        inited = true;
        }

        if (window.keyboard.isPressed(SDLK_ESCAPE)) {
            inited = false; pt = 3; return;
        }
        if (dead) return;

        // ---- 速度由慢到快 ----
        gameTime += dt;
        platSpd = PLAT_SPD_START + PLAT_SPD_RAMP * gameTime;
        if (platSpd > PLAT_SPD_MAX) platSpd = PLAT_SPD_MAX;

        // ---- 计分 ----
        scoreTimer += dt;
        if (scoreTimer >= 1.0f) { scoreTimer -= 1.0f; score += 1; }

        // ---- 生成平台 ----
        spawnTimer += dt;
        if (spawnTimer >= nextSpawn) {
            spawnTimer -= nextSpawn;
            nextSpawn = 1.8f + static_cast<float>(std::rand() % 1000) / 1000.0f;
            float dy = static_cast<float>((std::rand() % 150) - 75);
            float ny = plats.back().y + dy;
            if (ny < 130.0f) ny = 130.0f; else if (ny > 780.0f) ny = 780.0f;
            plats.push_back({SCRN_W + 50.0f, ny, 90.0f + static_cast<float>(std::rand() % 110), 14.0f});
        }

        // ---- 平台移动 ----
        for (auto &p : plats) p.x -= platSpd * dt;
        while (!plats.empty() && plats.front().x + plats.front().w < -50.0f) plats.erase(plats.begin());

        // ---- 主角物理 ----
        vx = onGround ? -platSpd : -platSpd * 0.5f;
        if (window.keyboard.isDown(SDLK_A))  vx -= PLYR_SPD;
        if (window.keyboard.isDown(SDLK_D))  vx += PLYR_SPD;
        if ((window.keyboard.isPressed(SDLK_SPACE) || window.keyboard.isPressed(SDLK_UP) || window.keyboard.isPressed(SDLK_W))
            && onGround) { vy = JUMP_VEL; onGround = false; }

        if (!onGround) vy += GRAVITY * dt;
        px += vx * dt;
        py += vy * dt;

        // ---- 平台碰撞 ----
        onGround = false;
        for (const auto &p : plats) {
            float top = p.y - p.thick * 0.5f;
            if (py + PLYR_HALF > top - 5.0f && py + PLYR_HALF < top + 12.0f && vy >= 0.0f) {
                if (px + PLYR_HALF > p.x + 4.0f && px - PLYR_HALF < p.x + p.w - 4.0f) {
                    py = top - PLYR_HALF; vy = 0.0f;
                    onGround = true; bounceCount = 0;
                    break;
                }
            }
        }

        // ---- 主角距水面距离判断 ----
        float distToWater = WATR_LVL - (py + PLYR_HALF);

        // ---- 落地涟漪（仅在主角靠近水面时扰动） ----
        if (onGround && vy == 0.0f && distToWater < CLOSE_DIST) {
            int cx = static_cast<int>(px / WDX);
            if (cx >= 0 && cx < WN) {
                float ripple = (1.0f - distToWater / CLOSE_DIST) * 2.0f;
                wyv[cx] -= ripple;
                if (cx > 0) wyv[cx-1] -= ripple * 0.5f;
                if (cx < WN-1) wyv[cx+1] -= ripple * 0.5f;
            }
        }

        // ---- 弹簧水交互（仅在主角接触水面时） ----
        bool inWater = (py + PLYR_HALF >= WATR_LVL && vy >= 0.0f);
        if (inWater && !onGround) {
            bounceCount++;
            if (bounceCount <= MAX_BOUNCES) {
                float bf = SPRING_K / static_cast<float>(bounceCount);
                vy = -vy * SPRING_DAMP * bf;
                if (vy > -40.0f) vy = -40.0f;
                py = WATR_LVL - PLYR_HALF - 1.0f;

                int cx = static_cast<int>(px / WDX);
                if (cx >= 0 && cx < WN) {
                    float imp = std::abs(vy) * 0.025f;
                    wyv[cx] -= imp;
                    for (int r = 1; r <= 3 && cx-r >= 0; r++) wyv[cx-r] -= imp * (1.0f - r*0.25f);
                    for (int r = 1; r <= 3 && cx+r < WN; r++) wyv[cx+r] -= imp * (1.0f - r*0.25f);
                }
                for (int i = 0; i < 8 + bounceCount * 4; i++) {
                    float angle = -1.57f + (static_cast<float>(std::rand())/RAND_MAX - 0.5f)*2.0f;
                    float speed = 60.0f + static_cast<float>(std::rand()%200);
                    splashes.push_back({px, WATR_LVL, std::cos(angle)*speed, std::sin(angle)*speed, 0.6f + static_cast<float>(std::rand()%40)/100.0f});
                }
            } else {
                dead = true;
                for (int i = 0; i < MAX_SPLASH; i++) {
                    float angle = -3.14f + static_cast<float>(std::rand())/RAND_MAX*3.14f;
                    float speed = 80.0f + static_cast<float>(std::rand()%300);
                    splashes.push_back({px, WATR_LVL, std::cos(angle)*speed, std::sin(angle)*speed, 0.5f + static_cast<float>(std::rand()%60)/100.0f});
                }
            }
        }

        if (!dead && px - PLYR_HALF <= 0.0f) dead = true;

        // ---- 正弦流动 + 弹簧模拟 ----
        wavePhase += WAVE_SPEED * dt;
        constexpr float SPREAD = 0.08f;
        constexpr float DAMP   = 0.985f;
        constexpr float EDGE   = 0.94f;

        for (int i = 1; i < WN - 1; i++) {
            // 正弦流动作为底层驱动
            float sinusDrive = std::sin(wavePhase + static_cast<float>(i) * WAVE_FREQ * 1600.0f) * WAVE_AMP;
            wyv[i] += (wyBase + sinusDrive - wy[i]) * 0.015f;  // 轻微向正弦波目标靠拢
            float leftPull  = wy[i-1] - wy[i];
            float rightPull = wy[i+1] - wy[i];
            wyv[i] += (leftPull + rightPull) * SPREAD;
            wyv[i] += (wyBase - wy[i]) * 0.002f;
            wyv[i] *= DAMP;
            wy[i]  += wyv[i] * dt;
        }
        wyv[0] *= EDGE;  wy[0] += wyv[0]*dt + (wyBase - wy[0])*0.01f;
        wyv[WN-1] *= EDGE; wy[WN-1] += wyv[WN-1]*dt + (wyBase - wy[WN-1])*0.01f;

        // ---- 飞溅粒子 ----
        for (auto &s : splashes) { s.x += s.vx*dt; s.y += s.vy*dt; s.vy += 300.0f*dt; s.life -= dt; }
        splashes.erase(std::remove_if(splashes.begin(), splashes.end(),
            [](const Splash &s) { return s.life <= 0.0f; }), splashes.end());
    });

    thread.wth_draw([&]() {
        draw.image(youklx::Imagecmd{image.ima[0][0], 0, 0, 1600, 900});

        // ---- 平台 ----
        for (const auto &p : plats) {
            if (p.x + p.w < 0.0f || p.x > SCRN_W) continue;
            float t = (platSpd - PLAT_SPD_START) / (PLAT_SPD_MAX - PLAT_SPD_START + 0.01f);
            int r = 160 - static_cast<int>(t * 60), g = 190 - static_cast<int>(t * 60), b = 190 - static_cast<int>(t * 80);
            platCmd.color(r, g, b);
            platCmd.from(static_cast<int>(p.x), static_cast<int>(p.y))
                   .to(static_cast<int>(p.x + p.w), static_cast<int>(p.y)).slw(p.thick);
            draw.line(platCmd);
        }

        // ---- 主角 ----
        if (!dead) {
            int cx = static_cast<int>(px), cy = static_cast<int>(py), hf = static_cast<int>(PLYR_HALF);
            int gr = 50 + bounceCount * 40, gg = 230 - bounceCount * 50, gb = 80;
            plyrCmd.color(gr, gg, gb);
            plyrCmd.from(cx-hf, cy).to(cx+hf, cy).slw(PLYR_SZ); draw.line(plyrCmd);
            plyrCmd.color(gr+60, gg+25, gb+40).slw(2.0f);
            plyrCmd.from(cx-hf, cy-hf).to(cx+hf, cy-hf); draw.line(plyrCmd);
            plyrCmd.from(cx+hf, cy-hf).to(cx+hf, cy+hf); draw.line(plyrCmd);
            plyrCmd.from(cx+hf, cy+hf).to(cx-hf, cy+hf); draw.line(plyrCmd);
            plyrCmd.from(cx-hf, cy+hf).to(cx-hf, cy-hf); draw.line(plyrCmd);
            plyrCmd.color(50, 230, 80);
        }

        // ---- 飞溅粒子 ----
        for (const auto &s : splashes) {
            float alpha = s.life / 1.0f; if (alpha > 1.0f) alpha = 1.0f;
            splashCmd.color(255, 255, 255, alpha);
            splashCmd.from(static_cast<int>(s.x), static_cast<int>(s.y))
                     .to(static_cast<int>(s.x+1), static_cast<int>(s.y+1)).slw(2.0f);
            draw.line(splashCmd);
        }

        // 水面：一条折线消除段间缝隙
        waterCmd.from(0, static_cast<int>(wy[0]));
        for (int i = 1; i < WN; i++)
            waterCmd.to(static_cast<int>(i * WDX), static_cast<int>(wy[i]));
        draw.line(waterCmd);

        // ---- UI（文字左对齐 80px） ----
        static constexpr float UI_X = 80.0f;
        char buf[64];
        std::snprintf(buf, sizeof(buf), "分数 %d", score);
        draw.font(youklx::Fontcmd{&font, buf}.sp(UI_X, 50).ss(52.0f).srgba({1.0f,1.0f,1.0f,1.0f}));
        std::snprintf(buf, sizeof(buf), "速度 Lv.%d", static_cast<int>((platSpd-PLAT_SPD_START)/5.0f)+1);
        draw.font(youklx::Fontcmd{&font, buf}.sp(UI_X, 110.0f).ss(28.0f).srgba({1.0f,0.85f,0.3f,0.8f}));
        draw.font(youklx::Fontcmd{&font, "A D 移动  SPACE 跳跃"}.sp(UI_X, 740.0f).ss(26.0f).srgba({1.0f,1.0f,1.0f,0.5f}));
        draw.font(youklx::Fontcmd{&font, "ESC 返回"}.sp(UI_X, 780.0f).ss(24.0f).srgba({1.0f,1.0f,1.0f,0.35f}));

        if (dead) {
            draw.image(youklx::Imagecmd{image.ima[0][0], 0,0,1600,900, 0,0,0,
                      {0,0,0,0.55f},{0,0,0,0.55f},{0,0,0,0.55f},{0,0,0,0.55f}});
            draw.font(youklx::Fontcmd{&font, "游戏结束"}.sp(664.0f, 260.0f).ss(68.0f).srgba({1.0f,0.3f,0.3f,1.0f}));
            std::snprintf(buf, sizeof(buf), "得分 %d", score);
            draw.font(youklx::Fontcmd{&font, buf}.sp(704.0f, 360.0f).ss(48.0f).srgba({1.0f,1.0f,1.0f,0.9f}));
            std::snprintf(buf, sizeof(buf), "速度等级 %d", static_cast<int>((platSpd-PLAT_SPD_START)/5.0f)+1);
            draw.font(youklx::Fontcmd{&font, buf}.sp(700.0f, 430.0f).ss(32.0f).srgba({1.0f,0.85f,0.3f,0.8f}));
            draw.font(youklx::Fontcmd{&font, "ESC 返回"}.sp(707.0f, 500.0f).ss(32.0f).srgba({1.0f,1.0f,1.0f,0.7f}));
        }
    });
}