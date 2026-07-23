namespace youklx {
    bool Keyboa::press(int key) {
        if (GetAsyncKeyState(key) & 0x8000) {
            ikey[ik1][ik2] = key;
            ik2 += 1;
            return true;
        } else {
            return false;
        }
    }
}
