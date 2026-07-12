namespace youklx {
    class Thread {
        public:
            #include"en/api/function.cpp"
            #include"中文/接口/函数.cpp"
        private:
            #include"en/internal/var.cpp"
            #include"en/internal/function.cpp"
        public:
            Thread();
            ~Thread();
    };
    using 线程 = Thread;
}
#include"main.cpp"
#include"en/pack.cpp"
#include"en/run.cpp"
#include"en/clear.cpp"
#include"en/wait.cpp"