namespace youklx {

bool Font::load(const char* ttfPath) {
    if (fontSize <= 0) fontSize = 20.0f;

    // 读取 TTF
    FILE* f = fopen(ttfPath, "rb");
    if (!f) return false;
    fseek(f, 0, SEEK_END);
    long fsz = ftell(f);
    fseek(f, 0, SEEK_SET);
    ttfData.resize(fsz);
    if (fread(ttfData.data(), 1, fsz, f) != (size_t)fsz) { fclose(f); return false; }
    fclose(f);

    // 初始化空图集
    atlasPages.clear();
    glyphs.clear();
    numPages = 0;
    cursorX = 0;
    cursorY = 0;
    atlasDirty = false;

    // 分配第一页
    atlasPages.push_back(std::vector<uint8_t>(atlasW * atlasH * 4, 0));
    numPages = 1;

    loaded = true;
    name = ttfPath;
    return true;
}

} // namespace youklx