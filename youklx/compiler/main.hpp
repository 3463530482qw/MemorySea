namespace youklx {
    class Compiler {
        public:
            #include"en/api/var.inl"
        public:
            #include"en/api/function.inl"
        private:
            #include"en/api/internal/var.inl"
            #include"en/api/internal/function.inl"
            #include"en/parameters/keyword/main.inl"
    };
    using 编译器 = Compiler;
}
#include "en/error.inl"
#include "en/read.inl"
#include "en/lexing.inl"
#include "en/stmt.inl"
#include "en/eval.inl"
#include "en/expr.inl"
#include "en/value.inl"
#include "en/declare.inl"
#include "en/void.inl"
#include "en/registry.inl"
#include "en/work/work.inl"