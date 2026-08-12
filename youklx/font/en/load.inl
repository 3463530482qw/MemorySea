namespace youklx {
    void Font::load(const char* ttfpath) {
        if (size <= 0.0f) size = 20.0f;

        // ① 二进制方式打开字体文件
        std::ifstream file(ttfpath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            throw std::runtime_error(std::string("字体文件打开失败: ") + ttfpath);
        }
        std::streamsize fsize = file.tellg();
        file.seekg(0, std::ios::beg);
        ttfData.resize(static_cast<size_t>(fsize));
        if (!file.read(reinterpret_cast<char*>(ttfData.data()), fsize)) {
            throw std::runtime_error(std::string("字体文件读取失败: ") + ttfpath);
        }
        // ③ 交给 stb_truetype 解析（0 表示从文件头开始）
        if (stbtt_InitFont(&fontInfo, ttfData.data(), 0) == 0) {
            throw std::runtime_error(std::string("字体解析失败(不是有效的TTF/OTF文件): ") + ttfpath);
        }
        // ④ 图集尺寸按当前字号同步(与 px 的公式一致)
        atlasW = static_cast<int>(size) * 32;
        atlasH = static_cast<int>(size) * 32;
    }
}
