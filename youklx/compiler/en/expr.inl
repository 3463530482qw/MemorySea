namespace youklx {
    double Compiler::expr() {
        if (pos >= toks.size()) throw std::runtime_error("表达式为空");
        size_t idx;
        double v = std::stod(toks[pos], &idx);
        if (idx != toks[pos].size()) throw std::runtime_error("非法数字: " + toks[pos]);
        pos++;
        while (pos < toks.size()) {
            if (toks[pos] == "+") {
                pos++;
                if (pos >= toks.size()) throw std::runtime_error("缺少加数");
                double add = std::stod(toks[pos], &idx);
                if (idx != toks[pos].size()) throw std::runtime_error("非法数字: " + toks[pos]);
                v += add;
                pos++;
            } else {
                throw std::runtime_error("不支持的运算符: " + toks[pos]);
            }
        }
        return v;
    }
}
