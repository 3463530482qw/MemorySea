namespace youklx {
    // 解出一个 UTF-8 字符并前进指针(中文 3 字节)
    char32_t Draw::utf8next(const char*& p) {
        unsigned char b0 = static_cast<unsigned char>(*p++);
        char32_t ch = b0;
        if ((b0 & 0xE0) == 0xC0) {
            unsigned char b1 = static_cast<unsigned char>(*p++);
            ch = ((static_cast<char32_t>(b0) & 0x1F) << 6) | (b1 & 0x3F);
        } else if ((b0 & 0xF0) == 0xE0) {
            unsigned char b1 = static_cast<unsigned char>(*p++);
            unsigned char b2 = static_cast<unsigned char>(*p++);
            ch = ((static_cast<char32_t>(b0) & 0x0F) << 12) | ((static_cast<char32_t>(b1) & 0x3F) << 6) | (b2 & 0x3F);
        } else if ((b0 & 0xF8) == 0xF0) {
            unsigned char b1 = static_cast<unsigned char>(*p++);
            unsigned char b2 = static_cast<unsigned char>(*p++);
            unsigned char b3 = static_cast<unsigned char>(*p++);
            ch = ((static_cast<char32_t>(b0) & 0x07) << 18) | ((static_cast<char32_t>(b1) & 0x3F) << 12)
                | ((static_cast<char32_t>(b2) & 0x3F) << 6) | (b3 & 0x3F);
        }
        return ch;
    }
}
