namespace youklx {

// 图片顶点：以cmd.x,cmd.y为左上角，cmd.w,cmd.h为宽高
std::vector<float> imageVertices(const Imagecmd& cmd) {
    auto c = [](const std::array<float,4>& col, int i) { 
        return (i < 3) ? col[i] / 255.0f : col[i]; 
    };
    float x1=cmd.x, y1=cmd.y;
    float x2=cmd.x+cmd.w, y2=cmd.y;
    float x3=cmd.x+cmd.w, y3=cmd.y+cmd.h;
    float x4=cmd.x, y4=cmd.y+cmd.h;
    if (cmd.rotate != 0.0f) {
        float cx=cmd.x + cmd.rox, cy=cmd.y + cmd.roy;
        float rad=cmd.rotate*3.14159265f/180.0f;
        float s=std::sin(rad),cs=std::cos(rad);
        auto rot=[&](float&px,float&py){
            float rx=px-cx,ry=py-cy;
            px=rx*cs-ry*s+cx; py=rx*s+ry*cs+cy;
        };
        rot(x1,y1); rot(x2,y2); rot(x3,y3); rot(x4,y4);
    }
    
    // 图集中图片间有 2px 透明 padding，无需 UV 收缩（uvClamp 已移除）
    float u0 = cmd.u0;
    float v0 = cmd.v0;
    float u1 = cmd.u1;
    float v1 = cmd.v1;
    
    return {
        x1,y1, u0,v0, c(cmd.c1,0),c(cmd.c1,1),c(cmd.c1,2),c(cmd.c1,3),
        x2,y2, u1,v0, c(cmd.c2,0),c(cmd.c2,1),c(cmd.c2,2),c(cmd.c2,3),
        x4,y4, u0,v1, c(cmd.c4,0),c(cmd.c4,1),c(cmd.c4,2),c(cmd.c4,3),
        x3,y3, u1,v1, c(cmd.c3,0),c(cmd.c3,1),c(cmd.c3,2),c(cmd.c3,3)
    };
}

}