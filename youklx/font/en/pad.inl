namespace youklx {
    void Font::pad(float em) {
        std::lock_guard lock(glyphMtx);   // 与 query/bake 并发安全
        if (padding == em) return;
        padding = em;

        // 留白变化后旧字形的距离场范围不对,清空图集与字形缓存重烤
        glyphs.clear();
        atlas.clear();
        cursorX = 0; cursorY = 0; rowH = 0;
        atlasVersion++;
    }
}
