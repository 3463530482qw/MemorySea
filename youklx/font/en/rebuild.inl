namespace youklx {
    // 内部:清空图集并重烤所有已缓存字符(图集满了时调用)
    void Font::rebuildAll(float scale) {
        std::unordered_map<char32_t, Glyph> old = std::move(glyphs);
        glyphs.clear();
        std::fill(atlas.begin(), atlas.end(), 0);
        cursorX = 0; cursorY = 0; rowH = 0;
        for (const auto& [ch, _] : old) {
            bake(ch, scale);
        }
        atlasVersion++;
    }
}
