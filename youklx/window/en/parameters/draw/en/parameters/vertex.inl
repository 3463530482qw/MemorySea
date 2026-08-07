namespace youklx {
    struct Vertex {                       // 通用顶点:对应着色器 inPosition/inUV/inColor
        float x{0.0f}, y{0.0f};           // 位置
        float u{0.0f}, v{0.0f};           // 纹理坐标
        float r{1.0f}, g{1.0f}, b{1.0f}, a{1.0f};  // 颜色
    };
}
