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
    static youklx::Linecmd curve{
        .thickness = 5
    };
    if(pts) {
        if (window.mouse.x >= 1250 && window.mouse.x <= 1450 && window.mouse.y >= 400 && window.mouse.y <= 520)

            pptt = 0;
        if (window.mouse.x >= 1250 && window.mouse.x <= 1450 && window.mouse.y >= 550 && window.mouse.y <= 670)
            pptt = 1;
        if (window.mouse.x >= 1250 && window.mouse.x <= 1450 && window.mouse.y >= 700 && window.mouse.y <= 820)
            pptt = 2;
        pptth = pptt * 150;

        rpt += window.time.different * 100;
        if (rpt > 360) rpt -= 360;

        ppttm = ppttm + (pptth - ppttm) * 5.0f * window.time.different;

        lda += window.time.different * 200;
        ldrg = 30;

        if(ppttb) {
            pptta += window.time.different * 0.5f;
            if(pptta >= 1.0) ppttb = false;
        } else {
            pptta -= window.time.different * 0.5f;
            if(pptta <= 0.6) ppttb = true;
        }

        draw.image(image.ima[0][0], 0, 0, 1600, 900);
        draw.image(image.ima[0][1], 0, 0, 1600, 900);

        // 绘制线条（发光效果）
        for (int i = 160; i > 0; --i) {
            float dist = fabs(i - center);
            if (dist > half_ldm)
                dist = ldm - dist;      // 环形距离处理

            float glowIntensity = 0.0f;
            if (dist < ldrg_f) {
                glowIntensity = 1.0f - dist / ldrg_f;   // 线性衰减
                glowIntensity *= glowIntensity;         // 平方曲线
            }

            // 灰度发光，RGB三通道相等，只算一次
            int rgb = 25 + static_cast<int>(204.0f * glowIntensity);
            float a = 0.5f + 0.5f * glowIntensity;

            curve.sp1(lx[i], ly[i]) 
                 .sp2(lx[i - 1], ly[i - 1])
                 .sr({rgb,rgb})
                 .sg({rgb,rgb})
                 .sb({rgb,rgb})
                 .sa({a, a});
            draw.line(curve);
        }

        // --- 后续UI绘制 ---
        draw.font(&font, "图形化界面展示", 100, 110, 120.0f, 0,0,0, {0.898f,0.898f,0.898f,1.0f});
        draw.font(&font, "开始", 1250, 400, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f});
        draw.font(&font, "设置", 1250, 550, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f});
        draw.font(&font, "结束", 1250, 700, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f});
    
        draw.image(image.ima[0][2], 1200, 380.0f + ppttm, 300, 120,0,0,0,
            {255,255,255,pptta},{255,255,255,pptta},
            {255,255,255,pptta},{255,255,255,pptta}
        );
        draw.image(image.ima[0][3], 1465, 425.0f + ppttm, 30, 30, rpt, 15, 15,
            {255,255,255,pptta},{255,255,255,pptta},
            {255,255,255,pptta},{255,255,255,pptta}
        );
    } else {
        draw.image(image.ima[0][0], 0, 0, 1600, 900);
        draw.image(image.ima[0][1], 0, 0, 1600, 900);
        for (int i = 160; i > 0; --i) {
            float dist = fabs(i - center);
            if (dist > half_ldm)
                dist = ldm - dist;      // 环形距离处理

            float glowIntensity = 0.0f;
            if (dist < ldrg_f) {
                glowIntensity = 1.0f - dist / ldrg_f;   // 线性衰减
                glowIntensity *= glowIntensity;         // 平方曲线
            }

            // 灰度发光，RGB三通道相等，只算一次
            int rgb = 25 + static_cast<int>(204.0f * glowIntensity);
            float a = 0.5f + 0.5f * glowIntensity;
            curve.sp1(lx[i], ly[i]) 
                 .sp2(lx[i - 1], ly[i - 1])
                 .sr({rgb,rgb})
                 .sg({rgb,rgb})
                 .sb({rgb,rgb})
                 .sa({a, a});
            draw.line(curve);
        }

        draw.font(&font, "图形化界面展示", 100, 110, 120.0f, 0,0,0, {0.898f,0.898f,0.898f,1.0f});
        draw.font(&font, "开始", 1250, 400, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f});
        draw.font(&font, "设置", 1250, 550, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f});
        draw.font(&font, "结束", 1250, 700, 120.0f, 0,0,0, {0.102f,0.102f,0.102f,1.0f});
    
        draw.image(image.ima[0][2], 1200, 380.0f + ppttm, 300, 120,0,0,0,
            {255,255,255,pptta},{255,255,255,pptta},
            {255,255,255,pptta},{255,255,255,pptta}
        );
        draw.image(image.ima[0][3], 1465, 425.0f + ppttm, 30, 30, rpt, 15, 15,
            {255,255,255,pptta},{255,255,255,pptta},
            {255,255,255,pptta},{255,255,255,pptta}
        );
        draw.image(image.ima[0][0], 0, 0, 1900, 900,rma1,0,900);
        draw.image(image.ima[0][0], 0, 900, 1900, 900,rma2);
        rma1 += window.time.different * 200;
        rma2 -= window.time.different * 100;
        if(rma1 >= 335) scene.ptr = "mselect";
    }

    if (window.mouse.leftPressed()&&pts == true) {
        if (isHoverStart) {
            pts = false;
        }
        if (isHoverSetting) {

        }
        if (isHoverEnd) {
            window.isrun = false; // 退出程序
        }
    }
}