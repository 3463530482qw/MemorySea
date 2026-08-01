namespace youklx {
    class Swapchain {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 交换链 = Swapchain;
}
#include "en/createSwapchain.inl"
#include "en/createImageViews.inl"
