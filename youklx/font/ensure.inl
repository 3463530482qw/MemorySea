namespace youklx {

void Font::ensure(const std::string& text) {
    if (!loaded || ttfData.empty()) return;

    // 一次性初始化字体信息，避免每个字符重复解析字体表
    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, ttfData.data(), 0)) return;
    float scale = stbtt_ScaleForPixelHeight(&info, fontSize);

    const char* p = text.c_str(), *e = p + text.size();
    while (p < e) {
        uint32_t cp = decodeUTF8(p, e);
        if (glyphs.find(cp) != glyphs.end()) continue;  // 已加载

        // 光栅化单个字形
        int w = atlasW, h = atlasH;
        int pcnt = w * h;
        int ix0, iy0, ix1, iy1;
        stbtt_GetCodepointBitmapBox(&info, cp, scale, scale, &ix0, &iy0, &ix1, &iy1);
        int gw = ix1 - ix0, gh = iy1 - iy0;
        if (gw <= 0 || gh <= 0) continue;

        // 检查当前页面剩余空间，不足则换行或翻页
        if (cursorX + gw > w) { cursorX = 0; cursorY += gh + 2; }
        if (cursorY + gh > h) {
            atlasPages.push_back(std::vector<uint8_t>(pcnt * 4, 0));
            numPages++;
            cursorX = 0; cursorY = 0;
        }

        std::vector<uint8_t> bitmap(gw * gh, 0);
        stbtt_MakeCodepointBitmap(&info, bitmap.data(), gw, gh, gw,
                                  scale, scale, cp);
        // 写入图集 RGBA
        for (int row = 0; row < gh; ++row) {
            int dstRow = cursorY + row;
            for (int col = 0; col < gw; ++col) {
                int dstOff = (dstRow * w + cursorX + col) * 4;
                uint8_t a = bitmap[row * gw + col];
                atlasPages.back()[dstOff + 0] = 255;
                atlasPages.back()[dstOff + 1] = 255;
                atlasPages.back()[dstOff + 2] = 255;
                atlasPages.back()[dstOff + 3] = a;
            }
        }

        // 记录 GlyphInfo
        GlyphInfo gi;
        gi.x0 = (float)cursorX / w;
        gi.y0 = (float)cursorY / h;
        gi.x1 = (float)(cursorX + gw) / w;
        gi.y1 = (float)(cursorY + gh) / h;
        gi.xoff = (float)ix0;
        gi.yoff = (float)iy0;
        int adv, lsb;
        stbtt_GetCodepointHMetrics(&info, cp, &adv, &lsb);
        gi.xadvance = adv * scale;
        gi.pageIndex = numPages - 1;

        glyphs[cp] = gi;
        cursorX += gw + 1;
        atlasDirty = true;
    }
}

} // namespace youklx