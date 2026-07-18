namespace youklx {
    Agent& Agent::sgo(std::vector<float>&& setgoal) {
        goal = std::move(setgoal);
        return *this;
    }
}