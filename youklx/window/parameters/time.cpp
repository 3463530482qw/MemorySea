namespace youklx {
    class Time {
        public:
            float current{0};
            float before{0};
            float different{0};
            float fps{0};          // 目标帧间隔（秒），0 表示不限制（使用硬件 VSync）
            bool vstart = true;
            std::chrono::steady_clock::time_point start{};

            // 帧时间滚动平均（用于平滑帧率监测）
            static constexpr int HISTORY_SIZE = 64;
            float frameHistory[HISTORY_SIZE]{};
            int historyIndex{0};
            int historyCount{0};
            float averageFrameTime{0};

        public:
            void update() {
                if(vstart) {
                    start = std::chrono::steady_clock::now();
                #ifdef _WIN32
                    // 将 Windows 定时器分辨率提升至 1ms，大幅改善 sleep_until 精度
                    timeBeginPeriod(1);
                #endif
                    vstart = false;
                }
                before = current;
                current = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::steady_clock::now() - start
                ).count() / 1000.f;

                // 定期重置基准点，防止浮点精度下降。
                // 同时重置 before/current 避免不同步导致负值尖峰。
                if (current > 3600.0f) {
                    start = std::chrono::steady_clock::now();
                    before = 0.0f;
                    current = 0.0f;
                }
                different = current - before;

                // 更新滚动平均帧时间
                if (different > 0 && different < 1.0f) {
                    frameHistory[historyIndex] = different;
                    historyIndex = (historyIndex + 1) % HISTORY_SIZE;
                    if (historyCount < HISTORY_SIZE) historyCount++;

                    float sum = 0;
                    for (int i = 0; i < historyCount; i++) sum += frameHistory[i];
                    averageFrameTime = sum / historyCount;
                }

                // 软件帧率限制：仅当 fps > 0 且本帧渲染过快时执行
                // 当使用硬件 VSync (Vulkan FIFO) 时，外部应设 fps = 0 禁用此限制
                if (fps > 0 && fps > different) {
                    float remaining = fps - different;
                    auto targetTime = std::chrono::steady_clock::now()
                        + std::chrono::duration<float>(remaining);

                    // 先睡眠到目标时间前 1.5ms，留余量防止 sleep_until 超时
                    const auto sleepMargin = std::chrono::microseconds(1500);
                    auto sleepUntil = targetTime - sleepMargin;
                    if (sleepUntil > std::chrono::steady_clock::now()) {
                        std::this_thread::sleep_until(sleepUntil);
                    }

                    // 自旋等待精确对齐到目标时间（约 1.5ms 内，CPU 开销可控）
                    while (std::chrono::steady_clock::now() < targetTime) {
                        // 自旋等待
                    }
                }
            };
    };
}