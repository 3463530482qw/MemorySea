namespace youklx {
    void Time::time() {
        before = current;
        current = std::chrono::duration<double>(
            std::chrono::steady_clock::now() - start
        ).count();

        // 定期重置基准点，防止浮点精度下降
        if (current > 86400.0f) {
            start = std::chrono::steady_clock::now();
            before   = 0.0f;
            current  = 0.0f;
            return;
        }
        dt = current - before;
    }
}