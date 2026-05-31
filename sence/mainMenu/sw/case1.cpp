void splashScreenAnimation1(int &pt) {
    static float ah = 0.01f;
    static float ew = 0.01f;
    
    ew =-(4.0f * (ah - 0.5f) * (ah - 0.5f) - 2);
    ah += ew * window.time.different * 0.9;

    draw.image(image.ima[0][0],0,0,1600,900);

    draw.font(&font, "图形化界面展示", 440, 405, 120.0f, 0, 0, 0, {1.0f, 1.0f, 1.0f, ah});

    if(ah > 1) pt = 2;
}
