namespace youklx {
    void Time::update() {
        for(auto& ufun : tfun) {
            ufun();
        }        
    }
}