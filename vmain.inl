#ifdef _WIN32
#include "youklx/wiall.hpp"
#else

#endif

#define API __declspec(dllexport)

API youklx::场景 场景;
API youklx::线程 线程;
API youklx::图片 图片;
API youklx::火山 火山;
API youklx::窗口 窗口;

// Vulkan 绘制实现仅编译进主可执行文件（Vulkan-Hpp RAII dispatch table 不可跨 DLL 模块）
#include "youklx/window/en/parameters/wvulkan/en/drawFrame.inl"