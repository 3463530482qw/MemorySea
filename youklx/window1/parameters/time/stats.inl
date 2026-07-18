namespace youklx {
    void Time::update_stats() {
        if (dt > 0 && dt < 1.0f) {
            if (emaFrameTime == 0.0f)
                emaFrameTime = dt;
            else
                emaFrameTime = EMA_ALPHA * dt + (1.0f - EMA_ALPHA) * emaFrameTime;
        }
    }
}
