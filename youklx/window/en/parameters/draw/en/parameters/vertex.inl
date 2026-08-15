namespace youklx {
    struct Vertex {                       // 通用顶点:对应着色器 inPosition/inUV/inColor/inEffects/inOutlineColor
        float x{0.0f}, y{0.0f};           // 位置
        float u{0.0f}, v{0.0f};           // 纹理坐标
        float r{1.0f}, g{1.0f}, b{1.0f}, a{1.0f};  // 正文颜色
        float ow{0.0f}, aa{0.02f};        // 描边宽度、抗锯齿带宽(SDF d 值,0 = 无描边)
        float fx{0.0f}, fy{0.0f};         // 对齐占位(与着色器 vec4 布局匹配)
        float ocr{0.0f}, ocg{0.0f}, ocb{0.0f}, oca{1.0f};  // 描边色
    };
}
