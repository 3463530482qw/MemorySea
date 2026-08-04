namespace youklx {
    // 报错并标记程序应停止执行
    void Compiler::error(const std::string& msg) {
        std::cerr << "第" << linen << "行: " << msg << '\n';
        errored = true;
    }
}
