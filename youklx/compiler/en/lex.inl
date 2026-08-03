namespace youklx {
    void Compiler::lex() {
        for (size_t i = 0; i < src.size();) {
            char c = src[i];
            if (std::isspace(static_cast<unsigned char>(c))) { i++; continue; }
            if (c == '+') { toks.push_back("+"); i++; continue; }
            if (std::isdigit(static_cast<unsigned char>(c))) {
                size_t j = i;
                while (j < src.size() && (std::isdigit(static_cast<unsigned char>(src[j])) || src[j] == '.')) j++;
                toks.push_back(src.substr(i, j - i));
                i = j;
                continue;
            }
            throw std::runtime_error(std::string("无法识别的字符: ") + c);
        }
    }
}
