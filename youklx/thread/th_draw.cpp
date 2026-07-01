namespace youklx {
    void Thread::wth_draw(std::function<void()> work) {
        // 首次调用时创建绘制线程（仅一次）
        if (!th_draw.joinable()) {
            th_draw = std::thread([this]() {
                while (true) {
                    {
                        std::unique_lock<std::mutex> lock(mtx_draw);
                        cv_draw_ready.wait(lock, [this]() { return draw_ready || stopw; });
                        if (stopw) return;
                    }

                    draw_work();

                    {
                        std::lock_guard<std::mutex> lock(mtx_draw);
                        draw_done = true;
                        draw_ready = false;
                    }
                    cv_draw_done.notify_one();
                }
            });
        }

        // 仅存储工作，由 wth_update 内部触发执行
        draw_work = std::move(work);
        draw_work_stored = true;
    }
}