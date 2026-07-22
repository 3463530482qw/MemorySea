namespace youklx {
    void Time::sfps() {
        if (dt < slpfps) {
            return;
        }
        float remaining = slpfps - dt;
        auto targetTime = std::chrono::steady_clock::now()
            + std::chrono::duration<float>(remaining);
        std::this_thread::sleep_until(targetTime);
    }
}