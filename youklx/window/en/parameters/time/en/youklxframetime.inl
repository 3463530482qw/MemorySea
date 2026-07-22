namespace youklx {
    void Time::youklxframetime() {
        youkt += dt;
        youkt = youktc / ((fabs(youkt) + 1.0f)*(fabs(youkt) + 2.0f));
    }
}