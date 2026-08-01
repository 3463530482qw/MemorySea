namespace youklx {
    class Swapchain {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
        private:
            #include "en/api/internal/var.inl"
    };
    using 交换链 = Swapchain;
}
#include "en/createswapchain.inl"