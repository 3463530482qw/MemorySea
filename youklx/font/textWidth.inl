namespace youklx {

float Font::textWidth(const std::string& text, float drawSize) {
    ensure(text);
    if (!loaded) return 0;
    float s = drawSize / fontSize;
    float x = 0;
    const char* p = text.c_str(), *e = p + text.size();
    while (p < e) {
        uint32_t cp = decodeUTF8(p, e);
        auto it = glyphs.find(cp);
        x += (it != glyphs.end()) ? it->second.xadvance * s : drawSize * 0.5f;
    }
    return x;
}

} // namespace youklx