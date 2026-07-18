namespace youklx {
    Agent& Agent::sfunact(std::string_view setfunact) {
        if (act.find(std::string(setfunact)) == act.end()) return *this;
        funact = setfunact;
        curact = act[funact];
        dcuract = dact[funact];
        return *this;
    }
}