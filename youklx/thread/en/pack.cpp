namespace youklx {
    template<uint8_t tnths>
    Thread<tnths>& Thread<tnths>::update_pack(std::function<void()> vpack) {
        update_tasks.push_back(std::move(vpack));
        return *this;
    }

    template<uint8_t tnths>
    Thread<tnths>& Thread<tnths>::draw_pack(std::function<void()> vpack) {
        draw_tasks.push_back(std::move(vpack));
        return *this;
    }
}