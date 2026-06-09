namespace youklx {
    void Thread::wth_draw(std::function<void()> work) {
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

        draw_work = std::move(work);

        {
            std::lock_guard<std::mutex> lock(mtx_draw);
            draw_ready = true;
            draw_done = false;
        }
        cv_draw_ready.notify_one();

        {
            std::unique_lock<std::mutex> lock(mtx_draw);
            cv_draw_done.wait(lock, [this]() { return draw_done; });
        }
    }
}