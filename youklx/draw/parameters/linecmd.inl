namespace youklx {
    // 折线顶点：坐标 + 颜色（0~1 浮点）
    struct LinePoint {
        int x{0}, y{0};
        float r{1.0f}, g{1.0f}, b{1.0f}, a{1.0f};
    };

    class Linecmd {
        public:
            // 折线顶点列表，每对相邻顶点构成一段线段
            std::vector<LinePoint> points{{0,0}, {10,10}};
            float thickness{1.0f};       //线宽
            int rotate{0}, rox{10}, roy{10};
            std::string lable{"line"};   //绘制类型
            float penR{1.0f}, penG{1.0f}, penB{1.0f}, penA{1.0f};  // 当前画笔色（可独立初始化）
        public:
            // 设置画笔色（r/g/b: 0~255, a: 0~1），后续顶点自动使用此色
            Linecmd& color(int r, int g, int b, float a = 1.0f) {
                penR = r/255.f; penG = g/255.f; penB = b/255.f; penA = a;
                return *this;
            }
            // 清空并设置起始顶点（使用当前画笔色）
            Linecmd& from(int x, int y) {
                points.clear();
                points.push_back({x, y, penR, penG, penB, penA});
                return *this;
            }
            // 追加顶点（使用当前画笔色）
            Linecmd& to(int x, int y) {
                points.push_back({x, y, penR, penG, penB, penA});
                return *this;
            }
            Linecmd& slw(float thicknes) { thickness=thicknes;return *this; }
            Linecmd& srot(int ro,int rx,int ry) { rotate=ro;rox=rx;roy=ry;return *this; }
    };
}