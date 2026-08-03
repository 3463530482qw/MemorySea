namespace youklx {
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
#include "en/lex.inl"
#include "en/parse.inl"
#include "en/run.inl"
#include "en/work.inl"
#include "en/registry.inl"