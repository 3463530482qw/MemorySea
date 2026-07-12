namespace youklx {
    template<uint8_t tnths>
    Thread<tnths>& Thread<tnths>::clear() {
        update_tasks.clear();
        draw_tasks.clear();
        return *this;
    }
}