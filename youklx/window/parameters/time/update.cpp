namespace youklx {
    void Time::update() {
        update_clock();
        update_stats();
        apply_limiter();
    }

    void Time::update_clock() {
        if (vstart) {
            start = std::chrono::steady_clock::now();
        #ifdef _WIN32
            timeBeginPeriod(1);
        #endif
            vstart = false;
        }
        before = current;
        current = std::chrono::duration<float>(
            std::chrono::steady_clock::now() - start
        ).count();

        // 定期重置基准点，防止浮点精度下降
        if (current > 3600.0f) {
            start = std::chrono::steady_clock::now();
            before   = 0.0f;
            current  = 0.0f;
            return;
        }
        dt = current - before;
    }
}
