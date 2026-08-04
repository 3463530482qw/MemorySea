namespace youklx {
    // 求值一段 token 的加法表达式（[begin, end)），返回结果，不输出
    // 加法运算符支持 "+" 和 "加"
    double Compiler::evaluate(size_t begin, size_t end) {
        size_t n = end - begin;
        if (n == 0 || n % 2 == 0) {
            error("表达式不完整（只支持 数字 + 数字）");
            return 0;
        }
        double v = val(token[begin]);
        for (size_t i = begin + 1; i < end; i += 2) {
            if (token[i] != "+" && token[i] != "加") {
                error("只支持加法，不认识的运算符 \"" + token[i] + "\"");
                return 0;
            }
            v += val(token[i + 1]);
        }
        return v;
    }
}
