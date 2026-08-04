// 关键字表：值直接存动作（成员函数指针），stmt 查表后直接调用
static inline std::unordered_map<std::string, void(Compiler::*)()> keyword = {
    {"+" , &Compiler::eval},
    {"加" , &Compiler::eval},
    {"int" , &Compiler::declare},
    {"整形" , &Compiler::declare},
    {"void" , &Compiler::declare_void},
    {"空" , &Compiler::declare_void},
};
