namespace youklx { 
    class Time {
        public:
            float current{0};
            float before{0};
            float different{0};
            float fps{0};
            bool vstart = true;
            std::chrono::steady_clock::time_point start{};
        public:
            void update() {
                if(vstart) {
                    start = std::chrono::steady_clock::now();
                    vstart = false;
                }
                if (current > 100) {
                    current = current - (int)current % 100;
                    start = start + std::chrono::seconds(100);
                }
                before = current;
                current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() / 1000.f;
                different = current - before;
                if(fps > different) {
                    std::this_thread::sleep_for(std::chrono::duration<double>(fps - different));
                }
            };
    };
}