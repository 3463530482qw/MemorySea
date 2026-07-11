namespace youklx {
    template<uint8_t tnths = 64>
    class Thread {
        public:
            #include"en/api/function.cpp"
            #include"中文/接口/函数.cpp"
        private:
            #include"en/parameters/tnths.cpp"
            #include"en/internal/var.cpp"
        public:
            Thread();
    };
    using 线程 = Thread<>;
}
#include"main.cpp"
#include"en/pack.cpp"