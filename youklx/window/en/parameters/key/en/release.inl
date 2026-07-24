namespace youklx {
    bool Keyboa::release(int key) {
        for (int i = 0; i <= ik2s; i++) {
            if (ikey[ik1s][i] == key) {
                break;
            } else if (i == ik2s) {
                return false;
            }
        }
        for (int i = 0; i <= ik2; i++) {
            if (ikey[ik1][i] == key) {
                return false;
            }
        }
        if(GetAsyncKeyState(key) & 0x8000) {
            ikey[ik1][ik2] = key;
            ik2 += 1;
            return false;
        } else {
            return true;
        }
    }
}