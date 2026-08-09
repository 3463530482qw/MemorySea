namespace youklx {
    // 内部:把单个字形烤进图集,返回 true 表示成功放入
    bool Font::bake(char32_t ch, float scale, int& out_w, int& out_h, int& out_xoff, int& out_yoff) {
        out_w = 0; out_h = 0; out_xoff = 0; out_yoff = 0;
        // stb_truetype 返回每像素字节数(1=灰度)
        unsigned char* bmp = stbtt_GetCodepointBitmap(&fontInfo, scale, scale, static_cast<int>(ch), &out_w, &out_h, &out_xoff, &out_yoff);
        if (!bmp || out_w <= 0 || out_h <= 0) { stbtt_FreeBitmap(bmp, nullptr); return false; }

        // 位图补成正方形:边长 = max(宽,高),字形居中,四边补 0(透明)
        // 正方形位图打包整齐,字形完整不越界,UV/偏移都按正方形算
        int side = std::max(out_w, out_h);
        std::vector<unsigned char> square(static_cast<size_t>(side) * side, 0);
        int ox = (side - out_w) / 2, oy = (side - out_h) / 2;
        for (int y = 0; y < out_h; y++) {
            std::memcpy(square.data() + static_cast<size_t>(oy + y) * side + ox, bmp + y * out_w, out_w);
        }
        stbtt_FreeBitmap(bmp, nullptr);

        // 行式打包:当前行放不下 → 换行
        if (cursorX + side + 1 > atlasW) { cursorX = 0; cursorY += rowH + 1; rowH = 0; }
        // 图集纵向放不下 → 重建(重烤已有字符)
        if (cursorY + side + 1 > atlasH) { rebuildAll(scale); return bake(ch, scale, out_w, out_h, out_xoff, out_yoff); }

        // 拷贝到图集
        for (int y = 0; y < side; y++) {
            std::memcpy(atlas.data() + (cursorY + y) * atlasW + cursorX, square.data() + y * side, side);
        }

        Glyph g;
        g.u0 = static_cast<float>(cursorX) / atlasW;
        g.v0 = static_cast<float>(cursorY) / atlasH;
        g.u1 = static_cast<float>(cursorX + side) / atlasW;
        g.v1 = static_cast<float>(cursorY + side) / atlasH;
        g.xoff = out_xoff; g.yoff = out_yoff;
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
