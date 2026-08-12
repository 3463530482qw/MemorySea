namespace youklx {
    struct FontPushConsts {   // 推常量:内存布局须与 font.vert 一致(mat4 mvp + 3 float,共 76B)
        float mvp[16];
        float screenW, screenH, snapPixel;
    };
}
