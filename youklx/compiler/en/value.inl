namespace youklx {
    // 取操作数数值：数字直接解析，否则查 global 变量表
    // void 空值默认视为 0，可参与运算
    double Compiler::val(const std::string& t) {
        try {
            return std::stod(t);
        } catch (...) {
            auto it = global.find(t);
            if (it == global.end()) {
                error("未声明的变量 \"" + t + "\"");
                return 0;
            }
            if (!it->second.has_value()) {
                return 0; // void 空值默认视为 0
            }
            try {
                return std::any_cast<double>(it->second);
            } catch (...) {
                error("变量 \"" + t + "\" 不是数字类型");
                return 0;
            }
        }
    }
}
