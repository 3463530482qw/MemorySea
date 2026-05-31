namespace youklx {

// 8-float 顶点格式: x,y, u,v, r,g,b,a
// 多页图集竖直堆叠为单张纹理，UV 由 pageIndex 偏移
std::vector<float> fontVertices(const Fontcmd& cmd) {
    if (!cmd.font || !cmd.font->loaded || cmd.text.empty()) return {};

    Font* font = cmd.font;
    float scale = cmd.fontSize / font->fontSize;
    float invPages = 1.0f / (float)(font->numPages > 0 ? font->numPages : 1);

    float cx = cmd.x + cmd.rox, cy = cmd.y + cmd.roy;
    float penX = 0, penY = 0;
    std::vector<float> verts;

    const char* p = cmd.text.c_str(), *e = p + cmd.text.size();
    while (p < e) {
        uint32_t cp = decodeUTF8(p, e);
        auto it = font->glyphs.find(cp);
        if (it == font->glyphs.end()) { penX += cmd.fontSize * 0.5f; continue; }

        GlyphInfo& g = it->second;
        float gx0 = penX + g.xoff * scale,  gy0 = penY;  // 基线作为字形顶部
        float gx1 = gx0 + (g.x1-g.x0) * font->atlasW * scale;
        float gy1 = gy0 + (g.y1-g.y0) * font->atlasH * scale;

        // 竖直堆叠: V 偏移 = pageIndex / numPages，V 范围 = 1/numPages
        float voff = (float)g.pageIndex * invPages;

        auto rot = [&](float& px, float& py) {
            if (cmd.rotate == 0) return;
            float rad = cmd.rotate * 3.14159265f / 180.0f;
            float s = std::sin(rad), cs = std::cos(rad);
            float rx = px - cx, ry = py - cy;
            px = rx*cs - ry*s + cx; py = rx*s + ry*cs + cy;
        };

        float r = cmd.rgba[0], gv = cmd.rgba[1], b = cmd.rgba[2], a = cmd.rgba[3];

        // TriangleList: 6 vertices with adjusted V
        float v[6][8] = {
            {cmd.x+gx0, cmd.y+gy0, g.x0, g.y0*invPages+voff, r,gv,b,a},
            {cmd.x+gx1, cmd.y+gy0, g.x1, g.y0*invPages+voff, r,gv,b,a},
            {cmd.x+gx0, cmd.y+gy1, g.x0, g.y1*invPages+voff, r,gv,b,a},
            {cmd.x+gx1, cmd.y+gy0, g.x1, g.y0*invPages+voff, r,gv,b,a},
            {cmd.x+gx1, cmd.y+gy1, g.x1, g.y1*invPages+voff, r,gv,b,a},
            {cmd.x+gx0, cmd.y+gy1, g.x0, g.y1*invPages+voff, r,gv,b,a},
        };
        for (int vi = 0; vi < 6; ++vi) { rot(v[vi][0], v[vi][1]); }
        for (int vi = 0; vi < 6; ++vi) verts.insert(verts.end(), v[vi], v[vi]+8);

        penX += g.xadvance * scale;
    }
    return verts;
}

}