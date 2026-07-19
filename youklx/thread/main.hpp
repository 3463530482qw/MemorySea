namespace youklx {
    class Thread {
        public:
            #include"en/api/function.inl"
            #include"中文/接口/函数.inl"
        private:
            #include"en/api/internal/var.inl"
            #include"en/api/internal/function.inl"
        public:
            Thread();
            ~Thread();
    };
    using 线程 = Thread;
}
#include"main.inl"
#include"en/pack.inl"
#include"en/run.inl"
#include"en/clear.inl"
#include"en/wait.inl"