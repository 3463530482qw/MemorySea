namespace youklx {
    struct Linecmd {
        int x1{0}, y1{0}, x2{10}, y2{10};
        int rotate{0}, rox{10}, roy{10};
        std::array<int, 2> r{255,255};
        std::array<int, 2> g{255,255};
        std::array<int, 2> b{255,255};
        std::array<float, 2> a{1.0f,1.0f};
        std::string lable{"line"};   //绘制类型
    };
}
    