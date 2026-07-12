namespace youklx {
    Thread& Thread::run() {
        // ===== 阶段0：等待上一帧绘制完成 =====
        {
            std::unique_lock lock(mtx);
            cv.wait(lock, [this]() {
                return draw_done.load(std::memory_order_acquire);
            });
        }

        // ===== 阶段1：更新（同步等待完成） =====
        if (!update_tasks.empty()) {
            phase.store(Phase::UPDATE, std::memory_order_release);
            update_done.store(false, std::memory_order_release);
            {
                std::lock_guard lock(mtx);
                update_claimed.store(0, std::memory_order_relaxed);
                update_completed.store(0, std::memory_order_relaxed);
            }
            cv.notify_all();

            {
                std::unique_lock lock(mtx);
                cv.wait(lock, [this]() {
                    return update_done.load(std::memory_order_acquire);
                });
            }
        }

        // ===== 阶段2：绘制（后台并行，不等待） =====
        if (!draw_tasks.empty()) {
            phase.store(Phase::DRAW, std::memory_order_release);
            draw_done.store(false, std::memory_order_release);
            {
                std::lock_guard lock(mtx);
                draw_claimed.store(0, std::memory_order_relaxed);
                draw_completed.store(0, std::memory_order_relaxed);
            }
            cv.notify_all();
        }

        return *this;
    }
}