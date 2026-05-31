namespace youklx {

struct GlyphInfo {
    float x0, y0, x1, y1;  // UV (0~1)
    float xoff, yoff;
    float xadvance;
    int pageIndex{0};       // 页面索引
};

} // namespace youklx