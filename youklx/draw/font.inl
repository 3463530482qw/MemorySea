namespace youklx {

#ifdef _WIN32
// 智能编码转换：自动检测输入是 UTF-8 还是 GBK，统一转为 UTF-8
static std::string toUTF8(const std::string& input) {
    if (input.empty()) return input;

    // 先尝试以 UTF-8 解释，检测是否有无效序列
    int wlen = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS,
                                   input.c_str(), (int)input.size(), nullptr, 0);
    if (wlen > 0) {
        // 有效的 UTF-8，无需转换
        return input;
    }

    // UTF-8 解析失败 → 按系统 ANSI (GBK) 转 UTF-8
    wlen = MultiByteToWideChar(CP_ACP, 0, input.c_str(), (int)input.size(), nullptr, 0);
    if (wlen <= 0) return input;

    std::wstring wstr(wlen, L'\0');
    MultiByteToWideChar(CP_ACP, 0, input.c_str(), (int)input.size(), &wstr[0], wlen);
    int ulen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(),
                                   nullptr, 0, nullptr, nullptr);
    if (ulen <= 0) return input;
    std::string result(ulen, '\0');
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(),
                        &result[0], ulen, nullptr, nullptr);
    return result;
}
#else
static std::string toUTF8(const std::string& input) { return input; }
#endif

Draw& Draw::font(Fontcmd cmd) {
    // 统一文本为 UTF-8（调用者可能传入其它编码）
    cmd.text = toUTF8(cmd.text);
    // 若已设置字体对象，则按需加载字形到图集
    if (cmd.font) cmd.font->ensure(cmd.text);
    // 直接使用传入的 cmd（调用者已设置位置、大小、颜色等）
    commands[activeWrite].emplace_back(cmd);
    cptr[activeWrite] += 1;
    return *this;
}
}