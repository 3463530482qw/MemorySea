namespace youklx {
    void Keyboa::update() {
        ik1s = ik1;
        ik2s = ik2;
        ik1 = 1 - ik1;
        ik2 = 0;
        ikey[ik1][0] = 0;
    }
}