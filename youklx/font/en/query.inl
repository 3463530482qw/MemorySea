namespace youklx {
    Glyph Font::query(char32_t ch) {
        // 互斥保护:更新线程可能并发烘焙字形
        std::lock_guard lock(glyphMtx);
        auto it = glyphs.find(ch);
        if (it != glyphs.end()) return it->second;

        // 首次遇到:按当前 size 烘焙
        if (atlas.empty()) atlas.assign(static_cast<size_t>(atlasW) * atlasH, 0);
        float scale = stbtt_ScaleForPixelHeight(&fontInfo, size);
        int w, h, xo, yo;
        if (!bake(ch, scale, w, h, xo, yo))
            throw std::runtime_error(std::string("字形烘焙失败"));
        return glyphs.at(ch);
    }
}
