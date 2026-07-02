namespace youklx {
    class Time {
    public:
        // —— 时钟数据 ——
        std::chrono::steady_clock::time_point start{};
        float current{0};             // 启动以来总时间（秒）
        float before{0};              // 上一帧时间（秒），用于计算 dt
        float dt{0};                  // 本帧间隔（秒）
        bool vstart{true};            // 首次更新标志

        // —— 统计数据 ——
        float emaFrameTime{0};        // 帧时间的 EMA 平滑值
        static constexpr float EMA_ALPHA = 2.0f / 65.0f;  // 等效窗口 ≈ 64 帧

        // —— 限帧数据 ——
        int targetFps{0};             // 目标帧率，0 = 不限 / 硬件 VSync

    public:
        void update();                // 每帧调用：推进时钟 + 统计 + 限帧
        void set_target_fps(int v);   // 设置目标帧率

    private:
        void update_clock();
        void update_stats();
        void apply_limiter();
    };
}
