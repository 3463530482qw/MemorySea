namespace youklx {
    class Fontcmd {
        public:
            Font* font{nullptr};            // 字体对象指针
            std::string text;               // 要绘制的文字
            float x{0.0f}, y{0.0f};         // 绘制位置（左上角）
            float fontSize{20.0f};          // 文字大小
            float rotate{0.0f};             // 旋转角度
            float rox{0.0f}, roy{0.0f};     // 旋转中心偏移
            std::array<float, 4> rgba{1.0f, 1.0f, 1.0f, 1.0f}; // 文字颜色
            std::string lable{"font"};      // 绘制类型
        public:
            Fontcmd& sf(Font* fot) { font=fot;return *this; }
            Fontcmd& sc(std::string tex) { text=tex;return *this; }
            Fontcmd& sp(float sx, float sy) { x=sx;y=sy;return *this; }
            Fontcmd& ss(float fsize) { fontSize=fsize;return *this; }
            Fontcmd& srot(float ro,float rx,float ry) { rotate=ro;rox=rx;roy=ry;return *this; }
            Fontcmd& srgba(std::array<float, 4> srgba) { rgba=srgba;return *this;}

    };
}