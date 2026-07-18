namespace youklx {

void Font::clean() {
    atlasPages.clear();
    glyphs.clear();
    ttfData.clear();
    numPages = 0;
    cursorX = 0;
    cursorY = 0;
    atlasDirty = false;
    loaded = false;
}

} // namespace youklx