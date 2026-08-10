namespace youklx {
    // 内部:把单个字形烤进图集,返回 true 表示成功放入
    bool Font::bake(char32_t ch, float scale) {
        // stb_truetype 返回每像素字节数(1=灰度),失败时 w/h 为 0
        int w = 0, h = 0, xo = 0, yo = 0;
        unsigned char* bmp = stbtt_GetCodepointBitmap(&fontInfo, scale, scale, static_cast<int>(ch), &w, &h, &xo, &yo);
        if (!bmp || w <= 0 || h <= 0) { stbtt_FreeBitmap(bmp, nullptr); return false; }

        // 位图补成正方形:边长 = max(宽,高),字形居中,四边补 0(透明)
        // 正方形位图打包整齐,字形完整不越界,UV/偏移都按正方形算
        int side = std::max(w, h);
        std::vector<unsigned char> square(static_cast<size_t>(side) * side, 0);
        int ox = (side - w) / 2, oy = (side - h) / 2;
        for (int y = 0; y < h; y++) {
            std::memcpy(square.data() + static_cast<size_t>(oy + y) * side + ox, bmp + y * w, w);
        }
        stbtt_FreeBitmap(bmp, nullptr);

        // 行式打包:当前行放不下 → 换行
        if (cursorX + side + 1 > atlasW) { cursorX = 0; cursorY += rowH + 1; rowH = 0; }
        // 图集纵向放不下 → 重建(重烤已有字符)
        if (cursorY + side + 1 > atlasH) { rebuildAll(scale); return bake(ch, scale); }

        // 拷贝到图集
        for (int y = 0; y < side; y++) {
            std::memcpy(atlas.data() + (cursorY + y) * atlasW + cursorX, square.data() + y * side, side);
        }

        Glyph g;
        g.u0 = static_cast<float>(cursorX) / atlasW;
        g.v0 = static_cast<float>(cursorY) / atlasH;
        g.u1 = static_cast<float>(cursorX + side) / atlasW;
        g.v1 = static_cast<float>(cursorY + side) / atlasH;
        g.xoff = xo; g.yoff = yo;
        // advance:字距(advanceWidth * scale)
        int advanceW = 0, lsb = 0;
        stbtt_GetCodepointHMetrics(&fontInfo, static_cast<int>(ch), &advanceW, &lsb);
        g.advance = static_cast<float>(advanceW) * scale;

        glyphs.emplace(ch, g);
        cursorX += side + 1;
        rowH = std::max(rowH, side);
        atlasVersion++;
        return true;
    }
}
