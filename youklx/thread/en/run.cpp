namespace youklx {
    Thread& Thread::run() {
        // ===== 阶段1：等待上一帧绘制完成 =====
        {
            std::unique_lock lock(mtx);
            cv.wait(lock, [this]() {
                return draw_done.load(std::memory_order_acquire);
            });
        }

        // ===== 阶段2：启动更新任务，等待完成 =====
        if (!update_tasks.empty()) {
            update_done.store(false, std::memory_order_release);
            {
                std::lock_guard lock(mtx);
                update_claimed.store(0, std::memory_order_relaxed);
                update_completed.store(0, std::memory_order_relaxed);
                // 防止工作线程 fallthrough 时用过期的 draw_claimed 索引本帧 draw_tasks
                draw_claimed.store(draw_tasks.size(), std::memory_order_relaxed);
            }
            cv.notify_all();

            {
                std::unique_lock lock(mtx);
                cv.wait(lock, [this]() {
                    return update_done.load(std::memory_order_acquire);
                });
            }
        }

        // ===== 阶段3：启动绘制任务（后台并行，不等待） =====
        if (!draw_tasks.empty()) {
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