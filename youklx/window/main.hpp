namespace youklx {
    class Window{
        public:
            #include "en/api/var.cpp"
            #include "中文/接口/变量.cpp"
        public:
            #include "en/api/function.cpp"
            #include "中文/接口/函数.cpp"
        private:
        private:
        public:
            Window();
    };
    using 窗口 = Window;
}
#include "main.cpp"
#include "en/init.cpp"