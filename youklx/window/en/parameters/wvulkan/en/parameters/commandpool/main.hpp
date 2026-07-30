namespace youklx {
    class CommandPool {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 命令池 = CommandPool;
}
#include "en/createCommandPool.inl"
