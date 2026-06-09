namespace youklx {
    class Imagecmd {
        public:
            Plimage img{};              // 图片数据
            float x{0.0f}, y{0.0f};     // 位置
            float w{0.0f}, h{0.0f};     // 宽高缩放
            float rotate{0.0f};         // 旋转角度
            float rox{0.0f}, roy{0.0f}; // 旋转中心位置
            std::array<float, 4> c1{255.0f,255.0f,255.0f,1.0f}; // 左上 rgba
            std::array<float, 4> c2{255.0f,255.0f,255.0f,1.0f}; // 右上 rgba
            std::array<float, 4> c3{255.0f,255.0f,255.0f,1.0f}; // 右下 rgba
            std::array<float, 4> c4{255.0f,255.0f,255.0f,1.0f}; // 左下 rgba
            // 图集 UV（由 draw.image() 从 Plpng 提取）
            float u0{0.0f}, v0{0.0f}, u1{1.0f}, v1{1.0f};
            std::string lable{"image"};  // 绘制类型
        public:
            Imagecmd& si(Plimage image) { img=image;return *this; }
            Imagecmd& sp(float sx, float sy) { x=sx;y=sy;return *this; }
            Imagecmd& ss(float sw, float sh) { w=sw;h=sh;return *this; }
            Imagecmd& srot(float ro,float rx,float ry) { rotate=ro;rox=rx;roy=ry;return *this; }
            Imagecmd& rgba1(std::array<float, 4> sc1) { c1=sc1;return *this; }
            Imagecmd& rgba2(std::array<float, 4> sc2) { c2=sc2;return *this; }
            Imagecmd& rgba3(std::array<float, 4> sc3) { c3=sc3;return *this; }
            Imagecmd& rgba4(std::array<float, 4> sc4) { c4=sc4;return *this; }
    };
}
