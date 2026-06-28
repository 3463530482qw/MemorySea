namespace youklx {

    // 折线顶点生成：遍历 points 相邻对，每段生成 6 顶点 TriangleList
    std::vector<float> lineVertices(const Linecmd& cmd) {
        const auto& pts = cmd.points;
        if (pts.size() < 2) return {};
        float hw = cmd.thickness * 0.5f;

        std::vector<float> verts;
        verts.reserve((pts.size() - 1) * 6 * 8);

        for (size_t i = 0; i + 1 < pts.size(); ++i) {
            float fx0 = float(pts[i].x),     fy0 = float(pts[i].y);
            float fx1 = float(pts[i+1].x),   fy1 = float(pts[i+1].y);
            float dx = fx1 - fx0, dy = fy1 - fy0;
            float len = std::sqrt(dx*dx + dy*dy);
            if (len < 0.0001f) continue;
            float nx = -dy/len, ny = dx/len;

            // 每段直接使用顶点自身的颜色（逐顶点色）
            float sR = pts[i].r,   sG = pts[i].g,   sB = pts[i].b,   sA = pts[i].a;
            float eR = pts[i+1].r, eG = pts[i+1].g, eB = pts[i+1].b, eA = pts[i+1].a;

            float seg[] = {
                fx0-nx*hw, fy0-ny*hw, 0,0, sR,sG,sB,sA,
                fx0+nx*hw, fy0+ny*hw, 0,0, sR,sG,sB,sA,
                fx1-nx*hw, fy1-ny*hw, 0,0, eR,eG,eB,eA,

                fx0+nx*hw, fy0+ny*hw, 0,0, sR,sG,sB,sA,
                fx1+nx*hw, fy1+ny*hw, 0,0, eR,eG,eB,eA,
                fx1-nx*hw, fy1-ny*hw, 0,0, eR,eG,eB,eA,
            };
            verts.insert(verts.end(), std::begin(seg), std::end(seg));
        }
        return verts;
    }
}