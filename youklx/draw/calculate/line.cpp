namespace youklx {

// 计算线段顶点数据：返回 (x,y,r,g,b,a) × 4 顶点 = 24 floats
std::vector<float> lineVertices(const Linecmd& cmd) {
    float fx1 = static_cast<float>(cmd.x1);
    float fy1 = static_cast<float>(cmd.y1);
    float fx2 = static_cast<float>(cmd.x2);
    float fy2 = static_cast<float>(cmd.y2);

    float dx = fx2 - fx1;
    float dy = fy2 - fy1;
    float len = std::sqrt(dx * dx + dy * dy);
    if (len < 0.0001f) return {};

    float nx = -dy / len;
    float ny = dx / len;
    float hw = cmd.thickness * 0.5f;

    float r1 = cmd.r[0] / 255.0f, g1 = cmd.g[0] / 255.0f, b1 = cmd.b[0] / 255.0f, a1 = cmd.a[0];
    float r2 = cmd.r[1] / 255.0f, g2 = cmd.g[1] / 255.0f, b2 = cmd.b[1] / 255.0f, a2 = cmd.a[1];

    return {
        fx1 - nx * hw, fy1 - ny * hw, r1, g1, b1, a1,
        fx1 + nx * hw, fy1 + ny * hw, r1, g1, b1, a1,
        fx2 - nx * hw, fy2 - ny * hw, r2, g2, b2, a2,
        fx2 + nx * hw, fy2 + ny * hw, r2, g2, b2, a2
    };
}

}