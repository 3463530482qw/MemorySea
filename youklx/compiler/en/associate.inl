namespace youklx {
    void Compiler::associate() {
        wchar_t exe[MAX_PATH];
        DWORD n = GetModuleFileNameW(NULL, exe, MAX_PATH);
        if (n == 0 || n >= MAX_PATH) return;

        std::wstring cmd = L"cmd /k \"\"" + std::wstring(exe) + L"\" \"%1\"\"";
        HKEY k;
        if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Classes\\.yokc", 0, NULL, 0,
                            KEY_SET_VALUE, NULL, &k, NULL) == ERROR_SUCCESS) {
            RegSetValueExW(k, NULL, 0, REG_SZ, (const BYTE*)L"youklxcpp",
                           (DWORD)sizeof(L"youklxcpp"));
            RegCloseKey(k);
        }
        if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Classes\\youklxcpp\\shell\\open\\command",
                            0, NULL, 0, KEY_SET_VALUE, NULL, &k, NULL) == ERROR_SUCCESS) {
            RegSetValueExW(k, NULL, 0, REG_SZ, (const BYTE*)cmd.c_str(),
                           (DWORD)((cmd.size() + 1) * sizeof(wchar_t)));
            RegCloseKey(k);
        }
    }

    void Compiler::disassociate() {
        RegDeleteTreeW(HKEY_CURRENT_USER, L"Software\\Classes\\youklxcpp>");
        RegDeleteKeyW(HKEY_CURRENT_USER, L"Software\\Classes\\.yokc>");
    }
}
