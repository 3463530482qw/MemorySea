namespace youklx {
    class Compiler; // 前置声明，供符号表成员指针类型使用
    class Lexing {
        public:
            #include"en/api/var.inl"
        public:
            #include"en/api/function.inl"
            #include"../symbol/main.inl"
    };
    using 词法分析 = Lexing;
}
#include "en/run.inl"