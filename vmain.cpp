#include "youklx/iall.hpp"

#ifdef MYDLL_EXPORTS
  #define API __declspec(dllexport)
#else
  #define API __declspec(dllimport)
#endif

youklx::Window window;
youklx::Scene Scene;

extern API youklx::Window window;
extern API youklx::Scene Scene;