namespace youklx {
    void Keyboa::update() {
        ik1 += ik1s;
        ik1s = ik1 - ik1s;
        ik1 = ik1 - ik1s;
        ik2 = 0;
    }
}