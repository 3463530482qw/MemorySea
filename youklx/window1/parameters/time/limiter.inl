namespace youklx {
    void Time::set_target_fps(int v) {
        targetFps = (v > 0) ? v : 0;
    }
    void Time::apply_limiter() {
        if (targetFps <= 0) return;
        float targetInterval = 1.0f / static_cast<float>(targetFps);
        if (targetInterval <= dt) return;

        float remaining = targetInterval - dt;
        auto targetTime = std::chrono::steady_clock::now()
            + std::chrono::duration<float>(remaining);

        // 睡眠到目标时间前 1.5ms，留余量防止 sleep_until 超时
        const auto sleepMargin = std::chrono::microseconds(1500);
        auto sleepUntil = targetTime - sleepMargin;
        if (sleepUntil > std::chrono::steady_clock::now()) {
            std::this_thread::sleep_until(sleepUntil);
        }

        // 自旋精确对齐，每 64 次 yield 降低功耗
        int spins = 0;
        while (std::chrono::steady_clock::now() < targetTime) {
            if ((++spins & 63) == 0) std::this_thread::yield();
        }
    }
}
