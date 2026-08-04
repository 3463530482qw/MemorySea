namespace youklx {
    #include "en/parameters/token.inl"
    #include "en/parameters/expr.inl"
    class Compiler {
        public:
            #include"en/api/var.inl"
        public:
            #include"en/api/function.inl"
        private:
            #include"en/api/internal/var.inl"
            #include"en/api/internal/function.inl"
    };
    using 编译器 = Compiler;
}
#include "en/read.inl"
#include "en/registry.inl"
#include "en/work/lex.inl"
#include "en/work/parse.inl"
#include "en/work/eval.inl"
#include "en/work/work.inl"