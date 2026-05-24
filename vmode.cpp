#include "youklx/iall.hpp"

#ifdef YOUKLX_EXPORTS    // 只在 DLL 项目里定义这个宏
  #define API __declspec(dllexport)
#else
  #define API __declspec(dllimport)
#endif

extern API youklx::Window window;
extern API youklx::Scene  Scene;