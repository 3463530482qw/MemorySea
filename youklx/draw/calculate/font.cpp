namespace youklx {

// 为文字生成顶点数据：每个字符 6 顶点（2 个三角形 = TriangleList）
// 顶点格式：x,y, u,v, r,g,b,a（8个 float）
std::vector<float> fontVertices(const Fontcmd& cmd) {
    if (!cmd.font || !cmd.font->loaded || cmd.text.empty()) return {};

    Font* font = cmd.font;
    float scale = cmd.fontSize / font->fontSize;

    // 旋转中心在左上角 + 偏移
    float cx = cmd.x + cmd.rox;
    float cy = cmd.y + cmd.roy;

    float penX = 0.0f;
    float penY = 0.0f;
    std::vector<float> verts;

    const char* p = cmd.text.c_str();
    const char* end = p + cmd.text.size();

    while (p < end) {
        uint32_t cp = decodeUTF8(p, end);
        auto it = font->glyphs.find(cp);
        if (it == font->glyphs.end()) {
            penX += cmd.fontSize * 0.5f;
            continue;
        }

        GlyphInfo& g = it->second;

        // 四边形四个角（未旋转）
        float gx0 = penX + g.xoff * scale;
        float gy0 = penY + g.yoff * scale;
        float gx1 = gx0 + (g.x1 - g.x0) * font->atlasW * scale;
        float gy1 = gy0 + (g.y1 - g.y0) * font->atlasH * scale;

        auto rotate = [&](float& px, float& py) {
            if (cmd.rotate == 0.0f) return;
            float rad = cmd.rotate * 3.14159265f / 180.0f;
            float s = std::sin(rad), cs = std::cos(rad);
            float rx = px - cx, ry = py - cy;
            px = rx * cs - ry * s + cx;
            py = rx * s + ry * cs + cy;
        };

        // 6 个顶点的位置（TriangleList: 三角形1=A-B-C, 三角形2=B-D-C）
        float v[6][4] = {
            {cmd.x + gx0, cmd.y + gy0, g.x0, g.y0}, // A: 左上
            {cmd.x + gx1, cmd.y + gy0, g.x1, g.y0}, // B: 右上
            {cmd.x + gx0, cmd.y + gy1, g.x0, g.y1}, // C: 左下
            {cmd.x + gx1, cmd.y + gy0, g.x1, g.y0}, // B: 右上 (复用)
            {cmd.x + gx1, cmd.y + gy1, g.x1, g.y1}, // D: 右下
            {cmd.x + gx0, cmd.y + gy1, g.x0, g.y1}, // C: 左下 (复用)
        };

        for (int vi = 0; vi < 6; ++vi) {
            rotate(v[vi][0], v[vi][1]);
        }

        float r = cmd.rgba[0], gv = cmd.rgba[1], b = cmd.rgba[2], a = cmd.rgba[3];

        for (int vi = 0; vi < 6; ++vi) {
            verts.insert(verts.end(), {
                v[vi][0], v[vi][1], v[vi][2], v[vi][3], r, gv, b, a
            });
        }

        penX += g.xadvance * scale;
    }

    return verts;
}

}