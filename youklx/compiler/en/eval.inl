namespace youklx {
    // 表达式语句：求值一行并输出结果
    void Compiler::eval() {
        if (token.empty()) return;
        std::cout << evaluate(0, token.size()) << '\n';
    }
}
