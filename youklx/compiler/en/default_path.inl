namespace youklx {
    std::string Compiler::default_path() {
        wchar_t path[MAX_PATH];
        DWORD n = GetModuleFileNameW(NULL, path, MAX_PATH);
        if (n == 0 || n >= MAX_PATH) return {};
        wchar_t* slash = wcsrchr(path, L'\\');
        if (slash == NULL) return {};
        *(slash + 1) = L'\0';       /* 截到 exe 所在目录 */
        wcscat(path, L"main.yokc");  /* 拼上默认脚本名 */
        if (GetFileAttributesW(path) == INVALID_FILE_ATTRIBUTES) return {};
        /* 宽字符路径转 UTF-8 供 read 使用 */
        int len = WideCharToMultiByte(CP_UTF8, 0, path, -1, NULL, 0, NULL, NULL);
        std::string utf8((size_t)len - 1, '\0');
        WideCharToMultiByte(CP_UTF8, 0, path, -1, utf8.data(), len, NULL, NULL);
        return utf8;
    }
}
