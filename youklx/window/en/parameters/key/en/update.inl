namespace youklx {
    void Keyboa::update() {
        std::swap(ik1,ik1s);
        ik2s = ik2;
        ik2 = 0;
        ikey[ik1][0] = 0;
    }
}