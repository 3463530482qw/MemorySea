#include "parameters/glyph.cpp"
#include "parameters/decode.cpp"
namespace youklx {
    class Font {
    public:
        // ---- 字体属性 ----
        std::string name;          // 字体名称/路径
        float fontSize{20.0f};     // 打包时字号 (px)
        int atlasW{4096};          // 图集单页宽度
        int atlasH{256};           // 图集单页高度
        int numPages{0};           // 图集总页数
        std::vector<std::vector<uint8_t>> atlasPages;   // 多页 RGBA 像素数据
        std::unordered_map<uint32_t, GlyphInfo> glyphs;  // Unicode码点 → 字形信息
        bool loaded{false};        // 是否已加载成功

        // ---- 按需加载状态 ----
        std::vector<uint8_t> ttfData;   // 持久 TTF 数据
        int cursorX{0}, cursorY{0};     // 当前图集页写入位置
        bool atlasDirty{false};         // 图集有新增需要上传

    public:
        Font() = default;

        // 设置字体纹理渲染字号 + 图集单页尺寸（必须在 load 之前调用）
        Font& px(float size, int aw = 4096, int ah = 256);

        // 加载 TTF 文件（仅保存数据，不预打包字形）
        bool load(const char* ttfPath);

        // 确保文本中所有字符的字形已装入图集（按需光栅化）
        void ensure(const std::string& text);

        // 计算 UTF-8 文本的渲染宽度（内部自动确保字形已加载）
        float textWidth(const std::string& text, float drawSize);

        // 释放全部图集数据和字形缓存
        void clean();
        ~Font() { clean(); };
    };
}
#include "px.cpp"
#include "load.cpp"
#include "ensure.cpp"
#include "textWidth.cpp"
#include "clean.cpp"