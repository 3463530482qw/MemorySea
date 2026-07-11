namespace youklx {
    template<uint8_t tnths>
    Thread<tnths>& Thread<tnths>::pack(std::function<void()> vpack) {
        task.push_back(std::move(vpack));
        return *this;
    }
}