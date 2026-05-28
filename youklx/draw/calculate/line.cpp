namespace youklx {

// 4顶点TriangleStrip
std::vector<float> lineVertices(const Linecmd& cmd) {
    float fx1=float(cmd.x1),fy1=float(cmd.y1),fx2=float(cmd.x2),fy2=float(cmd.y2);
    float dx=fx2-fx1,dy=fy2-fy1;
    float len=std::sqrt(dx*dx+dy*dy);
    if(len<0.0001f) return {};
    float nx=-dy/len,ny=dx/len,hw=cmd.thickness*0.5f;
    float r1=cmd.r[0]/255.f,g1=cmd.g[0]/255.f,b1=cmd.b[0]/255.f,a1=cmd.a[0];
    float r2=cmd.r[1]/255.f,g2=cmd.g[1]/255.f,b2=cmd.b[1]/255.f,a2=cmd.a[1];
    // 纹理坐标统一为(0,0)，触发片段着色器的纯色绘制模式
    return {
        fx1-nx*hw, fy1-ny*hw, 0,0, r1,g1,b1,a1,
        fx1+nx*hw, fy1+ny*hw, 0,0, r1,g1,b1,a1,
        fx2-nx*hw, fy2-ny*hw, 0,0, r2,g2,b2,a2,
        fx2+nx*hw, fy2+ny*hw, 0,0, r2,g2,b2,a2
    };
}

}