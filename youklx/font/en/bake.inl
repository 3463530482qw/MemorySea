namespace youklx {
    // 内部:把单个字形烤成 SDF 放进图集,返回 true 表示成功放入
    bool Font::bake(char32_t ch, float scale) {
        // SDF 约定:0.5 是轮廓,值大于 0.5 在字形内(stb 的 onedge_value=128)。
        // 距离映射:128 个灰度值恰好铺满整个留白(pad),d=0/1 精确落在留白边界,
        // 边界外的零填充与边界连续;绘制侧按 1em = 0.5/pad 把 em 换算成 d 值
        const unsigned char onedge = 128;
        const float pds = padding > 0.0f ? 128.0f / (padding * size) : size / 8.0f;
        int padpx = static_cast<int>(std::ceil(padding * size));

        int w = 0, h = 0, xo = 0, yo = 0;
        unsigned char* sdf = stbtt_GetCodepointSDF(&fontInfo, scale, static_cast<int>(ch),
                                                   padpx, onedge, pds, &w, &h, &xo, &yo);
        if (!sdf || w <= 0 || h <= 0) { stbtt_FreeBitmap(sdf, nullptr); return false; }

        // 补成正方形:边长 = max(宽,高),字形居中,四边留白透明
        // 正方形位图打包整齐,字形完整不越界,UV/偏移都按正方形算
        int side = std::max(w, h);
        std::vector<unsigned char> square(static_cast<size_t>(side) * side, 0);
        int ox = (side - w) / 2, oy = (side - h) / 2;
        for (int y = 0; y < h; y++) {
            std::memcpy(square.data() + static_cast<size_t>(oy + y) * side + ox, sdf + y * w, w);
        }
        stbtt_FreeBitmap(sdf, nullptr);

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
