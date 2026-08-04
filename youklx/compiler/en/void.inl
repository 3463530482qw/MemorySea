namespace youklx {
    // void / 空 关键字：声明空值变量（void 变量名 或 空 变量名）
    void Compiler::declare_void() {
        if (token.size() != 2) {
            error("void/空 用法为 void 变量名 或 空 变量名（声明空值变量）");
            return;
        }
        if (!valid_name(token[1])) return;
        global[token[1]] = std::any{};
    }
}
