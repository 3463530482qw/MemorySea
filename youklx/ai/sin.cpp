namespace youklx {
    Agent& Agent::sin(std::vector<float>&& setinput) {
        input = std::move(setinput);
        return *this;
    }
}