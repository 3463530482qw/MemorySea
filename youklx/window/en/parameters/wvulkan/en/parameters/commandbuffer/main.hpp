namespace youklx {
    class CommandBuffer {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
    };
    using 命令缓冲 = CommandBuffer;
}
#include "en/createcommandbuffers.inl"
#include "en/recordcommandbuffers.inl"