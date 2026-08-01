namespace youklx {
    class Renderpass {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
        private:
            #include "en/api/internal/var.inl"
    };
    using 渲染通道 = Renderpass;
}
#include "en/createrenderpass.inl"