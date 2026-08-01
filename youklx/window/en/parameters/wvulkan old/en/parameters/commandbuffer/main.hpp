namespace youklx {
    class CommandBuffer {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 命令缓冲 = CommandBuffer;
}
#include "en/createCommandBuffers.inl"
