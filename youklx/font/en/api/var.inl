float size{20.0f};
float padding{0.0f};             // SDF 边缘留白(em):烘焙时超出字形包围盒的距离场范围
std::vector<unsigned char> ttfData;
stbtt_fontinfo fontInfo;
// 字形图集缓存(动态烘焙)
std::vector<unsigned char> atlas;     // 图集位图(A8,alpha=字形)
int atlasW{0}, atlasH{0};             // 图集尺寸(load 时按字号同步)
int cursorX{0}, cursorY{0}, rowH{0};  // 行式打包游标
std::atomic<uint64_t> atlasVersion{0};        // 图集版本(渲染侧检测变化)
std::unordered_map<char32_t, Glyph> glyphs;  // 字形缓存
std::mutex glyphMtx;                  // 图集/字形缓存互斥(更新线程并发烘焙)
