void splashScreenAnimation1(int &pt) {
    static float ah = 0.01f;
    static float ew = 0.01f;
    static youklx::Imagecmd bk = {
        .img = image.ima[0][0],
        .x = 0,
        .y = 0,
        .w = 1600,
        .h = 900
    };
    thread.wth_update([&]() {
        ew =-(4.0f * (ah - 0.5f) * (ah - 0.5f) - 2);
            ah += ew * window.time.different * 0.9;

    });
    thread.wth_draw([&]() {
        draw.image(bk);

        draw.font(youklx::Fontcmd{&font, "图形化界面展示", 440, 405, 120.0f, 0, 0, 0, {1.0f, 1.0f, 1.0f, ah}});

    });
    
    if(ah > 1) pt = 2;
}
