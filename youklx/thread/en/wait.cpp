namespace youklx {
    Thread& Thread::wait() {
        std::unique_lock lock(mtx);
        cv.wait(lock, [this]() {
            return update_done.load(std::memory_order_acquire)
                && draw_done.load(std::memory_order_acquire);
        });
        return *this;
    }
}