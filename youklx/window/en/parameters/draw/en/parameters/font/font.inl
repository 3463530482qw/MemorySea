namespace youklx {
    Draw& Draw::font(Fontcmd cmd) {
        // 接收一条字体绘制命令,把参数转成四边形顶点(两个三角形)存入通用顶点数据
        float w = cmd.fontSize * cmd.text.size();       // 粗略宽度,字形烘焙后按实际宽
        float x0 = cmd.x, y0 = cmd.y, x1 = x0 + w, y1 = y0 + cmd.fontSize;
        Vertex quad[4] = {
            {x0, y0, 0, 0, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
            {x1, y0, 1, 0, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
            {x1, y1, 1, 1, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
            {x0, y1, 0, 1, cmd.rgba[0], cmd.rgba[1], cmd.rgba[2], cmd.rgba[3]},
        };
        vertices.push_back(quad[0]);
        vertices.push_back(quad[1]);
        vertices.push_back(quad[2]);
        vertices.push_back(quad[0]);
        vertices.push_back(quad[2]);
        vertices.push_back(quad[3]);
        return *this;
    }
}
