#include "en/parameters/swapchain/main.hpp"
#include "en/parameters/renderpass/main.hpp"
#include "en/parameters/framebuffer/main.hpp"
#include "en/parameters/commandpool/main.hpp"
#include "en/parameters/synchronization/main.hpp"
#include "en/parameters/commandbuffer/main.hpp"
#include "en/parameters/fontrender/main.hpp"
namespace youklx {
    class Wvulkan {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
        private:
            #include "en/api/internal/var.inl"
        private:
            #include "en/api/internal/function.inl"
    };
    using 窗口火山 = Wvulkan;
}
#include "en/init/init.inl"
#include "en/drawframe.inl"
#include "en/recreate.inl"