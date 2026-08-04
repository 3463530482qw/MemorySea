namespace youklx {
    bool Compiler::read() {
        if (lineNumber == 0 && line.starts_with("\xEF\xBB\xBF")) line.erase(0, 3);
        linen++;
        return std::getline(file, line);
    }
}