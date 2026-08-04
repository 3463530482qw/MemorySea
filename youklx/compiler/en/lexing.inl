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
            if (len == 1 && c == ' ') {
                if (i > start) token.push_back(line.substr(start, i - start));
                start = i + 1;
            } else if (len == 1 && (c == '+' || c == '{' || c == '}' || c == ',')) {
                // 加号、花括号、逗号单独切出（与前后 token 分离）
                if (i > start) token.push_back(line.substr(start, i - start));
                token.push_back(line.substr(i, 1));
                start = i + 1;
            }
            i += len;
        }
        if (start < line.size()) token.push_back(line.substr(start));
    }
}