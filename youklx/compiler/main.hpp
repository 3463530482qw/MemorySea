namespace youklx {
    class Compiler {
        public:
            #include"en/api/var.inl"
            #include"中文/接口/变量.inl"
        public:
            #include"en/api/function.inl"
            #include"中文/接口/函数.inl"
        private:
            #include"en/api/internal/var.inl"
            #include"en/api/internal/function.inl"
    };
    using 编译器 = Compiler;
}
#include "en/associate.inl"
#include "en/default_path.inl"
#include "en/work.inl"
#include "en/read.inl"
#include "en/lex.inl"
#include "en/expr.inl"