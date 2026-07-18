namespace youklx {
    Thread& Thread::update_pack(std::function<void()> vpack) {
        update_tasks.push_back(std::move(vpack));
        return *this;
    }

    Thread& Thread::draw_pack(std::function<void()> vpack) {
        draw_tasks.push_back(std::move(vpack));
        return *this;
    }
}