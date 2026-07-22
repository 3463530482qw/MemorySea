namespace youklx {
    class Time {
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/var.inl"
            #include "en/api/internal/function.inl"
        public:
            Time();
            ~Time();
    };
    using 时间 = Time;
}
#include "main.inl"
#include "en/load.inl"
#include "en/router.inl"
#include "en/time.inl"
#include "en/sfps.inl"
#include "en/youklxframetime.inl"
#include "en/update.inl"