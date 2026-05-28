#pragma once
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <cstring>
#include <cstdint>
#include <cstdio>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace youklx {

// 单个字符的烘焙信息
struct GlyphInfo {
    float x0, y0, x1, y1;  // 在图集中的 UV 坐标（0~1）
    float xoff, yoff;       // 绘制偏移（像素单位，按烘焙字号）
    float xadvance;         // 前进量（像素单位，按烘焙字号）
};

// UTF-8 解码
inline uint32_t decodeUTF8(const char*& p, const char* end) {
    if (p >= end) return 0;
    unsigned char c = static_cast<unsigned char>(*p);
    uint32_t cp;
    int len;
    if (c < 0x80) { cp = c; len = 1; }
    else if ((c & 0xE0) == 0xC0) { cp = c & 0x1F; len = 2; }
    else if ((c & 0xF0) == 0xE0) { cp = c & 0x0F; len = 3; }
    else if ((c & 0xF8) == 0xF0) { cp = c & 0x07; len = 4; }
    else { ++p; return 0xFFFD; }
    for (int i = 1; i < len; ++i) {
        if (p + i >= end) { p += i; return 0xFFFD; }
        cp = (cp << 6) | (static_cast<unsigned char>(p[i]) & 0x3F);
    }
    p += len;
    return cp;
}

// 字体数据
class Font {
public:
    std::string name;
    float fontSize{20.0f};
    int atlasW{1024}, atlasH{1024};
    std::vector<uint8_t> atlasRGBA;
    std::unordered_map<uint32_t, GlyphInfo> glyphs;
    bool loaded{false};

public:
    Font() = default;

    // 从 TTF 文件加载字体
    // ranges: {{起始码点, 数量}, ...}，默认仅 ASCII
    // 图集会从 1024² 自动扩大至 2048² -> 4096² 直到成功
    bool load(const char* ttfPath, float size,
              const std::vector<std::pair<uint32_t, int>>& ranges = {})
    {
        fontSize = size;

        // 读取 TTF 文件
        FILE* f = fopen(ttfPath, "rb");
        if (!f) return false;
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);
        std::vector<uint8_t> ttfBuf(fsize);
        fread(ttfBuf.data(), 1, fsize, f);
        fclose(f);

        // 默认烘焙范围：ASCII
        std::vector<std::pair<uint32_t, int>> bakeRanges = ranges;
        if (bakeRanges.empty()) {
            bakeRanges.push_back({32, 95}); // ASCII 32~126
        }

        int totalGlyphs = 0;
        for (auto& r : bakeRanges) totalGlyphs += r.second;

        std::vector<stbtt_packedchar> packedChars(totalGlyphs);

        // 尝试不同图集尺寸（自动扩大直到打包成功）
        bool packed = false;
        for (int atlasDim : {1024, 2048, 4096}) {
            atlasW = atlasDim;
            atlasH = atlasDim;
            int atlasPixelCount = atlasW * atlasH;
            std::vector<uint8_t> atlasAlpha(atlasPixelCount, 0);

            stbtt_pack_context pc;
            if (!stbtt_PackBegin(&pc, atlasAlpha.data(), atlasW, atlasH, 0, 1, nullptr)) {
                continue;
            }
            stbtt_PackSetOversampling(&pc, 1, 1);

            // 逐范围烘焙
            int charOffset = 0;
            bool allOK = true;
            for (auto& r : bakeRanges) {
                stbtt_pack_range packRange;
                packRange.font_size = size;
                packRange.first_unicode_codepoint_in_range = static_cast<int>(r.first);
                packRange.num_chars = r.second;
                packRange.chardata_for_range = &packedChars[charOffset];
                packRange.array_of_unicode_codepoints = nullptr;
                packRange.h_oversample = 1;
                packRange.v_oversample = 1;
                int result = stbtt_PackFontRanges(&pc, ttfBuf.data(), 0, &packRange, 1);
                if (result == 0) {
                    allOK = false;
                    break;
                }
                charOffset += r.second;
            }
            stbtt_PackEnd(&pc);

            if (allOK) {
                // 将 alpha 图集转换为 RGBA
                atlasRGBA.resize(atlasPixelCount * 4);
                for (int i = 0; i < atlasPixelCount; ++i) {
                    atlasRGBA[i * 4 + 0] = 255;
                    atlasRGBA[i * 4 + 1] = 255;
                    atlasRGBA[i * 4 + 2] = 255;
                    atlasRGBA[i * 4 + 3] = atlasAlpha[i];
                }
                packed = true;
                break;
            }
        }

        if (!packed) return false;

        // 转换 stbtt_packedchar 到 GlyphInfo
        int idx = 0;
        for (auto& r : bakeRanges) {
            for (int i = 0; i < r.second; ++i) {
                uint32_t cp = static_cast<uint32_t>(r.first) + i;
                stbtt_aligned_quad q;
                float dummyX = 0, dummyY = 0;
                stbtt_GetPackedQuad(&packedChars[idx], atlasW, atlasH, 0,
                                     &dummyX, &dummyY, &q, 1);

                GlyphInfo gi;
                gi.x0 = q.s0;
                gi.y0 = q.t0;
                gi.x1 = q.s1;
                gi.y1 = q.t1;
                gi.xoff = q.x0;
                gi.yoff = q.y0;
                gi.xadvance = packedChars[idx].xadvance;
                glyphs[cp] = gi;
                ++idx;
            }
        }

        loaded = true;
        name = ttfPath;
        return true;
    }

    float textWidth(const std::string& text, float drawSize) const {
        if (!loaded) return 0.0f;
        float scale = drawSize / fontSize;
        float x = 0.0f;
        const char* p = text.c_str();
        const char* end = p + text.size();
        while (p < end) {
            uint32_t cp = decodeUTF8(p, end);
            auto it = glyphs.find(cp);
            if (it != glyphs.end()) {
                x += it->second.xadvance * scale;
            } else {
                x += drawSize * 0.5f;
            }
        }
        return x;
    }

    void clean() {
        atlasRGBA.clear();
        glyphs.clear();
        loaded = false;
    }

    ~Font() { clean(); }
};

} // namespace youklx