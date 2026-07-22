namespace youklx {
    Time::Time() {
        timeBeginPeriod(1);
        tfun.push_back([this]() { router(); });
    }
    Time::~Time() {
        timeEndPeriod(1);
    }
}