namespace youklx {
    // 变量名合法性：不能是数字、不能是关键字
    bool Compiler::valid_name(const std::string& t) {
        try {
            (void)std::stod(t);
            error("变量名不能是数字 \"" + t + "\"");
            return false;
        } catch (...) {}
        if (keyword.find(t) != keyword.end()) {
            error("变量名不能是关键字 \"" + t + "\"");
            return false;
        }
        return true;
    }

    // 变量声明：int 变量名[, 变量名...] [= 表达式 | {表达式}]...
    // 无初始化 → void 空值（参与运算按 0）
    void Compiler::declare() {
        if (token.size() < 2) {
            error("变量声明格式应为 int 变量名[, 变量名...]");
            return;
        }
        size_t i = 1;
        while (i < token.size()) {
            if (!valid_name(token[i])) return;
            std::string name = token[i++];
            bool isvoid = false;
            double v = 0;
            if (i < token.size() && token[i] == "=") {
                i++;
                size_t end = i;
                while (end < token.size() && token[end] != ",") end++;
                if (end == i) {
                    error("变量 \"" + name + "\" 缺少初始化值");
                    return;
                }
                if (end - i == 1 && token[i] == "void") isvoid = true;
                else v = evaluate(i, end);
                i = end;
            } else if (i < token.size() && token[i] == "{") {
                i++;
                size_t j = i;
                while (j < token.size() && token[j] != "}") j++;
                if (j >= token.size()) {
                    error("缺少右花括号 \"}\"");
                    return;
                }
                if (j == i || (j - i == 1 && token[i] == "void")) isvoid = true;
                else v = evaluate(i, j);
                i = j + 1;
            }
            global[name] = isvoid ? std::any{} : std::any(v);
            if (i < token.size() && token[i] == ",") {
                i++;
                if (i == token.size()) {
                    error("末尾不能有逗号");
                    return;
                }
            } else if (i < token.size()) {
                if (valid_name(token[i])) { // 是合法变量名 → 缺逗号
                    error("变量 \"" + token[i] + "\" 前缺少逗号");
                    return;
                }
                error("多余的 token \"" + token[i] + "\"");
                return;
            }
        }
    }
}
