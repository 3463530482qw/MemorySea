namespace youklx {
    void Compiler::lexing() {
        token.clear();
        size_t start = 0;
        for (size_t i = 0; i < line.size();) {
            unsigned char c = static_cast<unsigned char>(line[i]);
            size_t len;
            switch (c >> 4) {
                case 12: case 13: len = 2; break;
                case 14: len = 3; break;
                case 15: len = 4; break;
                default: len = 1; break;
            }
            if (i + len > line.size()) len = line.size() - i;
            if (
                len == 1 && c == ' ' ||
                c == '+' || c == '-' ||
                line.substr(i, len) == "加" ||
                line.substr(i, len) == "减"
            ) {
                // 空格是纯分隔符；运算符（+ 加 - 减）切出为独立 token
                if (!token.empty() && start == i && token.back() == line.substr(i, len) && line[i - 1] != ' ') {
                    // 连续运算符（++、--、加加、减减）：先追加到当前 token，start 更新即切到下一个 token
                    token.back() += line.substr(i, len);
                } else {
                    if (i > start) token.push_back(line.substr(start, i - start));
                    if (c != ' ') token.push_back(line.substr(i, len)); // 运算符单独切出
                }
                start = i + len;
            } else if (len == 1 && (c == '{' || c == '}' || c == ',')) {
                // 加号、花括号、逗号单独切出（与前后 token 分离）
                if (i > start) token.push_back(line.substr(start, i - start));
                token.push_back(line.substr(i, len));
                start = i + len;
            }
            i += len;
        }
        if (start < line.size()) token.push_back(line.substr(start));
    }
}
