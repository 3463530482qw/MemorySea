namespace youklx {
    struct fontblock {                   // 单字符的绘制矩形(收集一次,发射时共用)
        float x0{0}, y0{0}, x1{0}, y1{0}; // 屏幕位置
        float u0{0}, v0{0}, u1{0}, v1{0}; // 图集 uv
    };
}
