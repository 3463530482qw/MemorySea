struct Glyph {                       // 一个字形在图集中的位置与度量
    float u0{0}, v0{0}, u1{0}, v1{0}; // 图集 uv(归一化)
    int xoff{0}, yoff{0};             // 位图相对基线偏移
    float advance{0};                 // 水平前进量(像素)
};
