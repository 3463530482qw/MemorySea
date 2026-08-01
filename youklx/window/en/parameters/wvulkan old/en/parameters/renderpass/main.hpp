namespace youklx {
    class RenderPass {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 渲染通道 = RenderPass;
}
#include "en/createRenderPass.inl"
