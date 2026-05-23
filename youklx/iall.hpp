//cpp标准库
#include<iostream>
#include<variant>
#include<vector>
#include<string>
#include<any>
#include<unordered_map>
#include<stdexcept>
#include<functional>

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

//图片加载库
#include "stb_image.h"

//动画库
#include <spine-sdl-cpp.h>

//ini配置读取库
#include "ini.c"
#include "cpp/INIReader.cpp"

//自定义封装库
#include "image/main.hpp"
#include "window/main.hpp"
#include "sence/main.hpp"
#include "init.hpp"
#include "var.cpp"