#include "en/parameters/create/main.hpp"
#include "en/parameters/win/main.hpp"
namespace youklx {
    class Window {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include"en/api/internal/var.inl"
        private:
        public:
            ~Window();
    };
    using 窗口 = Window;
}
#include "main.inl"
#include "en/reinfo/reinfo.inl"
#include "en/create.inl"
#include "en/close.inl"
#include "en/positionAdjustment.inl"
#include "en/run.inl"