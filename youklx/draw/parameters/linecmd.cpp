namespace youklx {
    class Linecmd {
        public:
            int x1{0}, y1{0}, x2{10}, y2{10};
            float thickness{1.0f};       //线宽
            int rotate{0}, rox{10}, roy{10};
            std::array<int, 2> r{255,255};
            std::array<int, 2> g{255,255};
            std::array<int, 2> b{255,255};
            std::array<float, 2> a{1.0f,1.0f};
            std::string lable{"line"};   //绘制类型
        public:
            Linecmd& sp1(int x,int y) { x1=x;y1=y;return *this; }
            Linecmd& sp2(int x,int y) { x2=x;y2=y;return *this; }
            Linecmd& slw(float thicknes) { thickness=thicknes;return *this; }
            Linecmd& srot(int ro,int rx,int ry) { rotate=ro;rox=rx;roy=ry;return *this; }
            Linecmd& sr(std::array<int, 2> ra) { r=ra;return *this; }
            Linecmd& sg(std::array<int, 2> ga) { g=ga;return *this; }
            Linecmd& sb(std::array<int, 2> ba) { b=ba;return *this; }
            Linecmd& sa(std::array<float, 2> aa) { a=aa;return *this; }
    };
}