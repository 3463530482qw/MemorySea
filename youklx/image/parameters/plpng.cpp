namespace youklx {
    // 原始图片数据——始终为 4 通道 RGBA 未压缩像素
    class Plpng {
        public:
            unsigned char* data{nullptr};   // RGBA 像素 (stbi_load 强制 4 通道)
            int w{0};                       // 宽 (px)
            int h{0};                       // 高 (px)
            int channels{4};                // 固定为 4 (RGBA)
            // 纹理图集内的 UV 坐标（buildAtlas 中填充）
            float u0{0.0f}, v0{0.0f}, u1{1.0f}, v1{1.0f};
    };
}
