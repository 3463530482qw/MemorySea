namespace youklx {

inline uint32_t decodeUTF8(const char*& p, const char* end) {
    if (p >= end) return 0;
    unsigned char c = static_cast<unsigned char>(*p);
    uint32_t cp; int len;
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

} // namespace youklx