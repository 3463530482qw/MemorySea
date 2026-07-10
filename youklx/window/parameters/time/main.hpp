namespace youklx {
    class Time {
    public:
        // —— 时钟数据 ——
        std::chrono::steady_clock::time_point start{};
        float current{0};             // 启动以来总时间（秒）
        float* 当前时间{&current};
        float before{0};              // 上一帧时间（秒），用于计算 dt
        float* 之前时间{&before};
        float dt{0};                  // 本帧间隔（秒）
        float* 帧间隔{&dt};
        bool vstart{true};            // 首次更新标志
        bool* 首次更新{&vstart};

        // —— 统计数据 ——
        float emaFrameTime{0};        // 帧时间的 EMA 平滑值
        float* 平滑帧时间{&emaFrameTime};
        static constexpr float EMA_ALPHA = 2.0f / 65.0f;  // 等效窗口 ≈ 64 帧

        // —— 限帧数据 ——
        int targetFps{0};             // 目标帧率，0 = 不限 / 硬件 VSync
        int* 目标帧率{&targetFps};

    public:
        void update();                // 每帧调用：推进时钟 + 统计 + 限帧
        void 更新() { update(); }
        void set_target_fps(int v);   // 设置目标帧率
        void 设置目标帧率(int v) { set_target_fps(v); }

    private:
        void update_clock();
        void update_stats();
        void apply_limiter();
    };
}
