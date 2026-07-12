namespace youklx {
    Thread& Thread::clear() {
        wait();
        update_tasks.clear();
        draw_tasks.clear();
        return *this;
    }
}