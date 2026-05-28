namespace youklx {
    struct Imagecmd {
        Plimage img{};              // 图片数据
        float x{0.0f}, y{0.0f};     // 位置
        float w{0.0f}, h{0.0f};     // 宽高缩放
        float rotate{0.0f};         // 旋转角度
        float rox{0.0f}, roy{0.0f}; // 旋转中心位置
        std::array<float, 4> c1{1.0f,1.0f,1.0f,1.0f}; // 左上 rgba
        std::array<float, 4> c2{1.0f,1.0f,1.0f,1.0f}; // 右上 rgba
        std::array<float, 4> c3{1.0f,1.0f,1.0f,1.0f}; // 右下 rgba
        std::array<float, 4> c4{1.0f,1.0f,1.0f,1.0f}; // 左下 rgba
        std::string lable{"image"};  // 绘制类型
    };
}