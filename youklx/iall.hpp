// 强制源文件和执行字符集为 UTF-8（MinGW 兼容）
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#endif
#pragma execution_character_set("utf-8")

//cpp标准库
#include<iostream>
#include<variant>
#include<vector>
#include<string>
#include<any>
#include<unordered_map>
#include<unordered_set>
#include<stdexcept>
#include<functional>
#include<chrono>
#include<ctime>
#include<thread>

#include <algorithm>
#include <queue>
#include <fstream>
#include <cstring>
#include <array>
#include <cmath>

#ifdef _WIN32
    #include <windows.h>
    #define ildll(name) LoadLibraryA(name)
    #define igfunc(handle, name) GetProcAddress(handle, name)
    #define icdll(handle) FreeLibrary((HMODULE)handle)
#else
    #include <dlfcn.h>
    #define ildll(name) dlopen(name, RTLD_LAZY)
    #define gifunc(handle, name) dlsym(handle, name)
    #define icdll(handle) dlclose(handle)
#endif

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
#include <vulkan/vulkan_raii.hpp>

//自定义封装库
#include "font/main.hpp"
#include "image/main.hpp"
#include "window/main.hpp"
#include "scene/main.hpp"
#include "draw/main.hpp"
#include "vulkan/main.hpp"
#include "init.hpp"