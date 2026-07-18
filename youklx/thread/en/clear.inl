namespace youklx {
    Thread& Thread::clear() {
        wait();
        update_tasks.clear();
        draw_tasks.clear();
        phase.store(Phase::IDLE, std::memory_order_release);
        return *this;
    }
}