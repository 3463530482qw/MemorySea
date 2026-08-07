namespace youklx {
    void Font::px(float size) {
        std::lock_guard lock(glyphMtx);   // 与 query 并发安全
        if (this->size == size) return;   // 字号没变,无需重建
        this->size = size;

        // 调整图集尺寸:根据字号估算所需大小(大字需要更大图集)
        int needW = 1024, needH = 1024;
        if (size > 48)  { needW = 2048; needH = 2048; }
        else if (size > 32) { needW = 1536; needH = 1536; }
        if (needW != atlasW || needH != atlasH) {
            atlasW = needW;
            atlasH = needH;
        }

        // 清空图集与字形缓存(旧字形是旧字号烘焙的,必须重烤)
        atlas.clear();
        glyphs.clear();
        cursorX = 0; cursorY = 0; rowH = 0;
        atlasVersion++;   // 通知渲染侧重新上传
    }
}
