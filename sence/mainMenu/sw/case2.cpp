void splashScreenAnimation2(int &pt,std::array<int, 161> &lx,std::array<int, 161> &ly) {
    static int fw = 440;
    static int fh = 405;
    static int i1w = 0;
    static int i1h = 0;
    static int i1x = 0;
    static int i1y = 0;
    static int dl;
    static bool curveReady = true;
    static int fw2 = 1600;
    static int fh2 = 400;
    static int fw3 = 1600;
    static int fh3 = 550;
    static int fw4 = 1600;
    static int fh4 = 700;
    static bool fwh = true;
    static youklx::Imagecmd bk = {
        .img = image.ima[0][0],
        .x = 0,
        .y = 0,
        .w = 1600,
        .h = 900
    };
    static youklx::Imagecmd abk = {
        .img = image.ima[0][1],
    };
    static youklx::Linecmd curve;
    static bool curveInited = false;
    thread.wth_update([&]() {
    if (curveReady) {
        if (!curveInited) { curve.color(229, 229, 229, 0.05f).slw(5.0f); curveInited = true; }
        // 必经点（按 x 升序排列，共6个）
        const int n = 6;
        double xs[n] = {0.0, 100.0, 550.0, 1198.0, 1430.0, 1600.0};
        double ys[n] = {900.0, 791.0, 450.0, 230.0, 210.0, 210.0};

        // 计算自然三次样条的系数
        double h[n-1], alpha[n-2], l[n], mu[n-1], z[n], c[n], b[n-1], d[n-1];
        for (int i = 0; i < n-1; i++) {
            h[i] = xs[i+1] - xs[i];
        }
        for (int i = 1; i < n-1; i++) {
            alpha[i-1] = 3.0/h[i]*(ys[i+1]-ys[i]) - 3.0/h[i-1]*(ys[i]-ys[i-1]);
        }
        l[0] = 1.0;
        mu[0] = 0.0;
        z[0] = 0.0;
        for (int i = 1; i < n-1; i++) {
            l[i] = 2.0*(xs[i+1]-xs[i-1]) - h[i-1]*mu[i-1];
            mu[i] = h[i]/l[i];
            z[i] = (alpha[i-1] - h[i-1]*z[i-1])/l[i];
        }
        l[n-1] = 1.0;
        z[n-1] = 0.0;
        c[n-1] = 0.0;
        for (int j = n-2; j >= 0; j--) {
            c[j] = z[j] - mu[j]*c[j+1];
            b[j] = (ys[j+1]-ys[j])/h[j] - h[j]*(c[j+1]+2.0*c[j])/3.0;
            d[j] = (c[j+1]-c[j])/(3.0*h[j]);
        }

        for (int i = 0; i <= 160; i++) {
            double x = i * 10.0;
            lx[i] = static_cast<int>(x);
            int seg = 0;
            while (seg < n-2 && x > xs[seg+1]) seg++;
            double dx = x - xs[seg];
            double y = ys[seg] + b[seg]*dx + c[seg]*dx*dx + d[seg]*dx*dx*dx;
            ly[i] = static_cast<int>(std::round(y));
        }
        curveReady = false;
    }

    if ((fw <= 100 || fh <= 110) && fwh) {
        fw = 100;
        fh = 110;
        i1w = 1600;
        i1h = 900;
        i1x = 0;
        i1y = 0;
        dl = 0;
        fwh = false;
    } else if (fw > 100 || fh > 110) {
        fw = fw + (100 - fw) * window.time.different * 2.7;
        fh = fh + (110 - fh) * window.time.different * 2.3;
        if (fw2 < 1250 ) {} else { fw2 = fw2 + (1250 - fw2) * 6 * window.time.different; }
        if (fw3 < 1250 ) {} else { fw3 = fw3 + (1250 - fw3) * 4.5 * window.time.different; }
        if (fw4 < 1250 ) {} else { fw4 = fw4 + (1250 - fw4)  * 3 * window.time.different; }
        
        dl =  161 - static_cast<int>((static_cast<float>(440 - fw) / 340.0f) * 161);
        i1x = 1600 - i1w;
        i1y = 900 - i1h;
        i1w = i1w + 1 + i1x * 0.03f;
        i1h = i1h + 1 + i1y * 0.03f;
    }
    abk.sp(i1x, i1y).ss(i1w, i1h);
    });
    thread.wth_draw([&]() {
    draw.image(bk);
    draw.image(abk);

    for (int i = 160; i > dl; i--) {
        curve.from(lx[i], ly[i])
             .to(lx[i - 1], ly[i - 1]);
        draw.line(curve);
    }

    draw.font(youklx::Fontcmd{&font, "图形化界面展示", static_cast<float>(fw), static_cast<float>(fh), 120.0f,0,0,0,{0.898f,0.898f,0.898f,1.0f}});
    draw.font(youklx::Fontcmd{&font, "开始", static_cast<float>(fw2), static_cast<float>(fh2), 120.0f,0,0,0,{0.102f,0.102f,0.102f,1.0f}});
    draw.font(youklx::Fontcmd{&font, "设置", static_cast<float>(fw3), static_cast<float>(fh3), 120.0f,0,0,0,{0.102f,0.102f,0.102f,1.0f}});
    draw.font(youklx::Fontcmd{&font, "结束", static_cast<float>(fw4), static_cast<float>(fh4), 120.0f,0,0,0,{0.102f,0.102f,0.102f,1.0f}});
    });
    if(fwh == false && curveReady == false) pt = 3;
}