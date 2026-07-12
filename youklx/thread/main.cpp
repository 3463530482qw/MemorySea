namespace youklx {
    template<uint8_t tnths>
    Thread<tnths>::Thread() {
        auto haco = std::thread::hardware_concurrency();
        haco = haco == 0 ? 4 : haco;
        nths = static_cast<uint8_t>(haco > 2 ? haco - 2 : 1);
        if (nths > mnths) nths = mnths;
        // 创建常驻工作线程
        for (uint8_t i = 0; i < nths; ++i) {
            th_pool[i] = std::jthread([this](std::stop_token st) {
                while (!st.stop_requested()) {
                    {
                        std::unique_lock lock(mtx);
                        cv.wait(lock, [&]() {
                            return (update_claimed.load(std::memory_order_acquire) < update_tasks.size()
                                    && !update_done.load(std::memory_order_acquire))
                                || (draw_claimed.load(std::memory_order_acquire) < draw_tasks.size()
                                    && !draw_done.load(std::memory_order_acquire))
                                || st.stop_requested();
                        });
                    }
                    if (st.stop_requested()) return;

                    // 抢更新任务
                    size_t i = update_claimed.fetch_add(1, std::memory_order_relaxed);
                    if (i < update_tasks.size()) {
                        update_tasks[i]();
                        size_t done = update_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                        if (done == update_tasks.size()) {
                            {
                                std::lock_guard lk(mtx);
                                update_done.store(true, std::memory_order_release);
                            }
                            cv.notify_all();
                        }
                        continue;
                    }

                    // 抢绘制任务
                    i = draw_claimed.fetch_add(1, std::memory_order_relaxed);
                    if (i < draw_tasks.size()) {
                        draw_tasks[i]();
                        size_t done = draw_completed.fetch_add(1, std::memory_order_acq_rel) + 1;
                        if (done == draw_tasks.size()) {
                            {
                                std::lock_guard lk(mtx);
                                draw_done.store(true, std::memory_order_release);
                            }
                            cv.notify_all();
                        }
                        continue;
                    }
                    // 都没抢到就回去睡觉，等待下个阶段
                }
            });
        }
    }

    template<uint8_t tnths>
    Thread<tnths>::~Thread() {
        for (uint8_t i = 0; i < nths; ++i)
            th_pool[i].request_stop();
        cv.notify_all();
    }
}