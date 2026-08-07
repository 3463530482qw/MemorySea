float size{20.0f};
std::vector<unsigned char> ttfData;
stbtt_fontinfo fontInfo;
// 字形图集缓存(动态烘焙)
std::vector<unsigned char> atlas;     // 图集位图(A8,alpha=字形)
int atlasW{1024}, atlasH{1024};       // 图集尺寸
int cursorX{0}, cursorY{0}, rowH{0};  // 行式打包游标
std::atomic<uint64_t> atlasVersion{0};        // 图集版本(渲染侧检测变化)
std::unordered_map<char32_t, Glyph> glyphs;  // 字形缓存
std::mutex glyphMtx;                  // 图集/字形缓存互斥(更新线程并发烘焙)
