void splashScreenAnimation3(int &pt, std::array<int, 161> &lx, std::array<int, 161> &ly) {
    static int pptt = 0;
    static int pptth = 0;
    static float ppttm = 0;
    static int ldrg = 0;
    static int lda = 0;
    static int ldm = 160;
    static float rpt = 0;
    static float pptta = 0.1f;
    static bool ppttb = true;
    static bool pts = true;
    const float half_ldm = ldm * 0.5f;             
    const float ldrg_f   = static_cast<float>(ldrg);  
    const float center   = ldm - fmod(lda / 10.0f, static_cast<float>(ldm));
    bool isHoverStart = (window.mouse.x >= 1250 && window.mouse.x <= 1450 && 
                            window.mouse.y >= 400 && window.mouse.y <= 520);
    bool isHoverSetting = (window.mouse.x >= 1250 && window.mouse.x <= 1450 && 
                        window.mouse.y >= 550 && window.mouse.y <= 670);
    bool isHoverEnd = (window.mouse.x >= 1250 && window.mouse.x <= 1450 && 
                    window.mouse.y >= 700 && window.mouse.y <= 820);
    static float rma1 = 270.0f;
    static float rma2 = 0.0f;
    static bool transitionReset = true;
    static youklx::Linecmd curve{
        .thickness = 5
    };
    static youklx::Imagecmd bk = {
        .img = image.ima[0][0],
        .x = 0,
        .y = 0,
        .w = 1600,
        .h = 900
    };
    static youklx::Imagecmd abk = {
        .img = image.ima[0][1],
        .x = 0,
        .y = 0,
        .w = 1600,
        .h = 900
    };
    static youklx::Imagecmd pt1 = {
        .img = image.ima[0][2],
        .w = 300,
        .h = 120
    };
    static youklx::Imagecmd pt2 = {
        .img = image.ima[0][3],
        .w = 30,
        .h = 30
    };
    static youklx::Imagecmd an1 = {
        .img = image.ima[0][0],
        .w = 1900,
        .h = 900
    };
    static youklx::Imagecmd an2 = {
        .img = image.ima[0][0],
        .y = 900,
        .w = 1900,
        .h = 900
    };
    auto drawCommonUI = [&]() {
        draw.image(bk);
        draw.image(abk);

        // 曲线发光绘制
        for (int i = 160; i > 0; --i) {
            float dist = fabs(i - center);
            if (dist > half_ldm) dist = ldm - dist;

            float glowIntensity = 0.0f;
            if (dist < ldrg_f) {
                glowIntensity = 1.0f - dist / ldrg_f;
                glowIntensity *= glowIntensity;
            }

            int rgb = 25 + static_cast<int>(204.0f * glowIntensity);
            float a = 0.5f + 0.5f * glowIntensity;

            curve.sp1(lx[i], ly[i])
                 .sp2(lx[i - 1], ly[i - 1])
                 .sr({rgb, rgb}).sg({rgb, rgb}).sb({rgb, rgb}).sa({a, a});
            draw.line(curve);
        }

        // 文字
        draw.font(youklx::Fontcmd{&font, "图形化界面展示", 100, 110, 120.0f, 0,0,0, {0.898f,0.898f,0.898f,1.0f}});
        draw.font(youklx::Fontcmd{&font, "开始", 1250, 400, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f}});
        draw.font(youklx::Fontcmd{&font, "设置", 1250, 550, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f}});
        draw.font(youklx::Fontcmd{&font, "结束", 1250, 700, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f}});

        // 按钮选中背景和旋转图标（两个状态都要画）
        draw.image(pt1);
        draw.image(pt2);
    };

    thread.wth_update([&]() {
        if (pts) {
        transitionReset = true;
        // --- 修正悬停：先重置为 -1，无悬停时高亮消失 ---
        pptt = -1;
        if (isHoverStart) pptt = 0;
        if (isHoverSetting) pptt = 1;
        if (isHoverEnd) pptt = 2;

        pptth = (pptt == -1) ? pptth : pptt * 150;  // 无悬停时保持原位置或做平滑归位

        rpt += window.time.different * 100;
        if (rpt > 360) rpt -= 360;

        ppttm = ppttm + (pptth - ppttm) * 5.0f * window.time.different;

        lda += window.time.different * 200;
        ldrg = 30;

        // 透明度呼吸
        if (ppttb) {
            pptta += window.time.different * 0.5f;
            if (pptta >= 1.0) ppttb = false;
        } else {
            pptta -= window.time.different * 0.5f;
            if (pptta <= 0.6) ppttb = true;
        }
        } else {
        // 每次进入切换动画时，重置动画参数
        if (transitionReset) {
            rma1 = 270.0f;
            rma2 = 0.0f;
            transitionReset = false;
        }
        // 切换动画阶段：让动画继续，按钮淡出
        lda += window.time.different * 200;            // 光点继续流动
        pptta -= window.time.different * 0.8f;         // 逐渐透明
        if (pptta < 0.0f) pptta = 0.0f;

        rma1 += window.time.different * 200;
        rma2 -= window.time.different * 100;
        if (rma1 >= 335) scene.ptr = "mselect";
        }

    // --- 统一更新 pt1/pt2 属性（两个分支都会执行）---
    pt1.sp(1200, 380 + ppttm)
       .rgba1({255,255,255,pptta})
       .rgba2({255,255,255,pptta})
       .rgba3({255,255,255,pptta})
       .rgba4({255,255,255,pptta});
    pt2.sp(1465, 425 + ppttm)
        .srot(rpt, 15, 15)
        .rgba1({255,255,255,pptta})
        .rgba2({255,255,255,pptta})
        .rgba3({255,255,255,pptta})
        .rgba4({255,255,255,pptta});

        an1.srot(rma1, 0, 900);
        an2.srot(rma2, 0, 0);

    
    });
    thread.wth_draw([&]() {
    drawCommonUI();

    // 仅在切换态绘制额外的转场背景
    if (!pts) {
        draw.image(an1);
        draw.image(an2);
    }
    });

    // 点击事件
    if (window.mouse.leftPressed() && pts) {
        if (isHoverStart) pts = false;
        if (isHoverSetting) { /* 后续可扩展 */ }
        if (isHoverEnd) window.isrun = false;
    }
}