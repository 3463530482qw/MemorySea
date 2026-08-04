namespace youklx {
    // 语句分发：遍历 token 找关键字，从字典取出动作直接调用
    void Compiler::stmt() {
        for (size_t i = 0; i < token.size(); i++) {
            auto it = keyword.find(token[i]);
            if (it == keyword.end()) continue;
            (this->*it->second)();
            return;
        }
        eval(); // 没有关键字 → 按表达式求值
    }
}
