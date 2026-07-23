//cpp标准库
#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <any>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <functional>
#include <chrono>
#include <ctime>
#include <thread>

#include <algorithm>
#include <queue>
#include <fstream>
#include <cstring>
#include <array>
#include <cmath>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>

#include <windows.h>

//媒体库
#include "SDL_vulkan.h"

//图片加载库
#include "stb_image.h"

//字体加载库
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

//动画库
#include <spine-sdl-cpp.h>

//ini配置读取库
#include "ini.c"
#include "cpp/INIReader.cpp"

//图形库
#ifndef NDEBUG
#ifndef VULKAN_HPP_ASSERT
#define VULKAN_HPP_ASSERT(...) ((void)0)
#endif
#endif
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_raii.hpp>

namespace youklx {
    //重载模板
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
}
namespace 有棵黎夕的 = youklx;
//自定义封装库
#include "scene/main.hpp"
#include "thread/main.hpp"
//#include "font/main.hpp"
//#include "image/main.hpp"
#include "window/main.hpp"

//#include "draw/main.hpp"
//#include "vulkan/main.hpp"

#include "init.hpp"