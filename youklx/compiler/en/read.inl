namespace youklx {
    void Compiler::read(const std::string& path) {
        std::ifstream f(path);
        if (!f) throw std::runtime_error("无法打开脚本: " + path);
        src.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    }
}
