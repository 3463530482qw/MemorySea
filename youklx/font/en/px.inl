namespace youklx {
    void Font::px(float ssize) {
        std::lock_guard lock(glyphMtx);   // 与 query 并发安全
        if (size == ssize) return;   // 字号没变,无需重建
        size = ssize;

        atlasW = size * 32;
        atlasH = size * 32;

        // 清空图集与字形缓存(旧字形是旧字号烘焙的,必须重烤)
        atlas.clear();
        glyphs.clear();
        cursorX = 0; cursorY = 0; rowH = 0;
        atlasVersion++;
    }
}
