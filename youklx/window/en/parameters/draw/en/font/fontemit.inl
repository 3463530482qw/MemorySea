namespace youklx {
    // 发射一个字形 quad:矩形绕 (rox,roy) 旋转后写进命令顶点缓冲
    void Draw::fontemit(const Fontcmd& cmd, const fontblock& b, float cosr, float sinr) {
        float qx[4] = {b.x0, b.x1, b.x1, b.x0};
        float qy[4] = {b.y0, b.y0, b.y1, b.y1};
        if (cmd.rotate != 0.0f) {
            for (int i = 0; i < 4; i++) {
                float dx = qx[i] - cmd.rox, dy = qy[i] - cmd.roy;
                qx[i] = cmd.rox + dx * cosr - dy * sinr;
                qy[i] = cmd.roy + dx * sinr + dy * cosr;
            }
        }
        const int tri[6] = {0, 1, 2, 0, 2, 3};
        for (int i = 0; i < 6; i++) {
            int k = tri[i];
            float u = (k == 0 || k == 3) ? b.u0 : b.u1;
            float v = (k < 2) ? b.v0 : b.v1;
            cmd.vertices.push_back({qx[k], qy[k], u, v,
                                    cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]});
        }
    }
}
