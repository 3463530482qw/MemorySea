#ifdef _WIN32
#include "youklx/wiall.hpp"
#else

#endif

#define API __declspec(dllimport)

API youklx::场景 场景;
API youklx::线程 线程;
API youklx::窗口 窗口;