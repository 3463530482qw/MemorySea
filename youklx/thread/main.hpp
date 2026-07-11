namespace youklx {
    template<uint8_t tnths = 64>
    class Thread {
        private:
            #include"en/parameters/tnths.cpp"
            #include"en/internal/var.cpp"
        public:
            Thread();
    };
    using 线程 = Thread<>;
}
#include"main.cpp"