namespace youklx {
    bool Compiler::read() {
        if (linen == 1 && line.starts_with("\xEF\xBB\xBF")) line.erase(0, 3);
        linen++;
        return static_cast<bool>(std::getline(file, line));
    }
}