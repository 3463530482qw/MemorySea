namespace youklx {
    // 收集整段文字的单字符矩形:解码、取字形、算屏幕位置与 uv
    void Draw::fontblocks(const Fontcmd& cmd, float scale, std::vector<fontblock>& blocks) {
        float penX = cmd.x, penY = cmd.y;
        const char* p = cmd.text.c_str();
        while (*p) {
            Glyph g = cmd.fot->query(utf8next(p));   // 副本(锁内返回,避免引用失效)

            // UV 内缩半纹素:方形位图边缘与相邻字形间有 1px 空隙,内缩避免越界采样
            float u0 = g.u0 + 0.5f / cmd.fot->atlasW, v0 = g.v0 + 0.5f / cmd.fot->atlasH;
            float u1 = g.u1 - 0.5f / cmd.fot->atlasW, v1 = g.v1 - 0.5f / cmd.fot->atlasH;

            // 字形在屏幕上的大小 = 位图像素尺寸 × 字号缩放
            float gw = (g.u1 - g.u0) * cmd.fot->atlasW * scale;
            float gh = (g.v1 - g.v0) * cmd.fot->atlasH * scale;
            if (gw <= 0 || gh <= 0) { penX += g.advance * scale; continue; }   // 空白字符

            // 字形位图左上角(基线 yoff 偏移,同样按字号缩放)
            blocks.push_back({penX + g.xoff * scale, penY + g.yoff * scale,
                              penX + g.xoff * scale + gw, penY + g.yoff * scale + gh,
                              u0, v0, u1, v1});
            penX += g.advance * scale;
        }
    }
}
