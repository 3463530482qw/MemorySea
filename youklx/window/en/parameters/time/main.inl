namespace youklx {
    Time::Time() {
        timeBeginPeriod(1);
        tfun.push_back([this]() { time(); });
    }
    Time::~Time() {
        timeEndPeriod(1);
    }
}