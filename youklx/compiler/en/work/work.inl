namespace youklx {
    void Compiler::work(int cargc, char** cargv) {
        #include "init.inl"
        while (read()) {
            tokens = lex();                  // 分词
            if (tokens.empty()) continue;    // 本行出错，跳过
            pos = 0;                         // 从行首开始解析
            auto expr = parse();             // 解析成表达式树
            if (!expr) continue;             // 解析失败，跳过
            print(eval(*expr));              // 求值并打印
        }
    }
}
