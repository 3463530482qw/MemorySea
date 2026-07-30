#include "en/parameters/swapchain/main.hpp"
#include "en/parameters/renderpass/main.hpp"
#include "en/parameters/framebuffer/main.hpp"
#include "en/parameters/commandpool/main.hpp"
namespace youklx {
    class Wvulkan {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 窗口火山 = Wvulkan;
}
#include "en/createSurface.inl"
#include "en/findGraphicsQueueFamily.inl"
#include "en/createSwapchain.inl"
#include "en/createImageViews.inl"
#include "en/createRenderPass.inl"
#include "en/createFramebuffers.inl"
#include "en/createCommandPool.inl"