namespace youklx {
    Draw& Draw::font(const Fontcmd& cmd) {
        if (!cmd.fot) return *this;

        // 命令脏才重算顶点缓冲(写命令自己的缓冲;未调用设置函数则沿用,不更新顶点内容)
        if (cmd.dirty) {
            cmd.vertices.clear();
            // 缩放比例 = 目标字号 / 烘焙字号(位图按烘焙字号烤制,绘制时按比例缩放)
            float scale = cmd.fontSize / cmd.fot->size;
            float penX = cmd.x, penY = cmd.y;
            const char* p = cmd.text.c_str();
            while (*p) {
                // UTF-8 解码(中文 3 字节)
                unsigned char b0 = static_cast<unsigned char>(*p++);
                char32_t ch = b0;
                if ((b0 & 0xE0) == 0xC0) {
                    unsigned char b1 = static_cast<unsigned char>(*p++);
                    ch = ((static_cast<char32_t>(b0) & 0x1F) << 6) | (b1 & 0x3F);
                } else if ((b0 & 0xF0) == 0xE0) {
                    unsigned char b1 = static_cast<unsigned char>(*p++);
                    unsigned char b2 = static_cast<unsigned char>(*p++);
                    ch = ((static_cast<char32_t>(b0) & 0x0F) << 12) | ((static_cast<char32_t>(b1) & 0x3F) << 6) | (b2 & 0x3F);
                } else if ((b0 & 0xF8) == 0xF0) {
                    unsigned char b1 = static_cast<unsigned char>(*p++);
                    unsigned char b2 = static_cast<unsigned char>(*p++);
                    unsigned char b3 = static_cast<unsigned char>(*p++);
                    ch = ((static_cast<char32_t>(b0) & 0x07) << 18) | ((static_cast<char32_t>(b1) & 0x3F) << 12)
                        | ((static_cast<char32_t>(b2) & 0x3F) << 6) | (b3 & 0x3F);
                }

                Glyph g = cmd.fot->query(ch);   // 副本(锁内返回,避免引用失效)

                // UV 内缩半纹素:图集打包时字形间有 1px 空隙,不内缩会采样到相邻字形/空隙,边缘不全
                float u0 = g.u0 + 0.5f / cmd.fot->atlasW, v0 = g.v0 + 0.5f / cmd.fot->atlasH;
                float u1 = g.u1 - 0.5f / cmd.fot->atlasW, v1 = g.v1 - 0.5f / cmd.fot->atlasH;

                // 字形在屏幕上的大小 = 位图像素尺寸 × 字号缩放
                float gw = (g.u1 - g.u0) * cmd.fot->atlasW * scale;
                float gh = (g.v1 - g.v0) * cmd.fot->atlasH * scale;
                if (gw <= 0 || gh <= 0) { penX += g.advance * scale; continue; }   // 空白字符

                // 字形位图左上角(基线 yoff 偏移,同样按字号缩放)
                float x0 = penX + g.xoff * scale, y0 = penY + g.yoff * scale;
                float x1 = x0 + gw,     y1 = y0 + gh;

                // 旋转(绕 rox/roy)
                float cosr = std::cos(cmd.rotate), sinr = std::sin(cmd.rotate);
                auto rot = [&](float& vx, float& vy) {
                    float dx = vx - cmd.rox, dy = vy - cmd.roy;
                    vx = cmd.rox + dx * cosr - dy * sinr;
                    vy = cmd.roy + dx * sinr + dy * cosr;
                };
                Vertex quad[4] = {
                    {x0, y0, u0, v0, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
                    {x1, y0, u1, v0, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
                    {x1, y1, u1, v1, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
                    {x0, y1, u0, v1, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
                };
                if (cmd.rotate != 0.0f) {
                    for (auto& v : quad) rot(v.x, v.y);
                }
                cmd.vertices.push_back(quad[0]);
                cmd.vertices.push_back(quad[1]);
                cmd.vertices.push_back(quad[2]);
                cmd.vertices.push_back(quad[0]);
                cmd.vertices.push_back(quad[2]);
                cmd.vertices.push_back(quad[3]);

                penX += g.advance * scale;
            }
            cmd.dirty = false;
        }
        if (cmd.vertices.empty()) return *this;

        std::lock_guard lock(vertMtx);   // 并发 push 保护
        // 提交命令的顶点缓冲到顶点流
        size_t start = vertices.size();
        vertices.insert(vertices.end(), cmd.vertices.begin(), cmd.vertices.end());

        // 登记批次:连续同字体合并,不同字体另起一段(渲染端按段切换图集)
        size_t added = cmd.vertices.size();
        if (!batches.empty() && batches.back().font == cmd.fot) {
            batches.back().count += added;
        } else {
            batches.push_back({cmd.fot, start, added});
        }
        return *this;
    }
}
