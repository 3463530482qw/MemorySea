namespace youklx {
    Thread::Thread() {
        auto haco = std::thread::hardware_concurrency();
        haco = haco == 0 ? 4 : haco;
        nths = static_cast<uint16_t>(haco > 2 ? haco - 2 : 1);
        // 创建常驻工作线程
        for (uint16_t i = 0; i < nths; ++i) {
            th_pool.emplace_back([this](std::stop_token st) {
                while (!st.stop_requested()) {
                    {
                        std::unique_lock lock(mtx);
                        cv.wait(lock, [&]() {
                            if (st.stop_requested()) return true;
                            Phase p = phase.load(std::memory_order_acquire);
                            if (p == Phase::UPDATE)
                                return update_claimed.load(std::memory_order_acquire) < update_tasks.size();
                            if (p == Phase::DRAW)
                                return draw_claimed.load(std::memory_order_acquire) < draw_tasks.size();
                            return false; // IDLE：继续休眠
                        });
                    }
                    if (st.stop_requested()) return;

                    Phase p = phase.load(std::memory_order_acquire);

                    if (p == Phase::UPDATE) {
                        // 抢更新任务
                        size_t i = update_claimed.fetch_add(1, std::memory_order_acq_rel);
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
                        }
                        // 没抢到 → 回 cv.wait，等待阶段切换或下一批任务
                    } else if (p == Phase::DRAW) {
                        // 抢绘制任务
                        size_t i = draw_claimed.fetch_add(1, std::memory_order_acq_rel);
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
                        }
                        // 没抢到 → 回 cv.wait
                    }
                    // IDLE → 回 cv.wait
                }
            });
        }
    }

    Thread::~Thread() {
        wait();
        for (uint16_t i = 0; i < nths; ++i)
            th_pool[i].request_stop();
        cv.notify_all();
    }
}