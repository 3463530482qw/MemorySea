#include "en/parameters/itvinfo/main.hpp"
namespace youklx {
    class Vulkan {
        public:
            #include "en/api/var.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/var.inl"
    };
    using 火山 = Vulkan;
}
#include "en/instance.inl"
#include "en/pickPhysicalDevice.inl"
#include "en/init.inl"