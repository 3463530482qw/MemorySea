namespace youklx {
    Fontcmd::Fontcmd() : order(nextOrder.fetch_add(1, std::memory_order_relaxed)) {}
}
