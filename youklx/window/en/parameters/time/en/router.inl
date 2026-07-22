namespace youklx {
    void Time::router() {
        start = std::chrono::steady_clock::now();
        tfun.clear();
        slpfps = tfps - 0.000015;
        youktc = slpfps * (slpfps + 1.0f) * (slpfps + 2.0f);
        tfun.push_back([this]() { time(); });
        if (youkft) {
            tfun.push_back([this]() { youklxframetime(); });
        }
        tfun.push_back([this]() { sfps(); });
    }
}