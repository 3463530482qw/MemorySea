namespace youklx {
    bool Keyboa::hold(int key) {
        // 上一帧按过(已入缓存)→ 视为按住
        for (int i = 0; i <= ik2s; i++) {
            if (ikey[ik1s][i] == key) {
                return true;
            }
        }
        // 本帧按过 → 按住
        for (int i = 0; i <= ik2; i++) {
            if (ikey[ik1][i] == key) {
                return true;
            }
        }
        // 实时检测物理按键(首次按下也能捕获)
        if (GetAsyncKeyState(key) & 0x8000) {
            if (ik2 < ikey[ik1].size()) {
                ikey[ik1][ik2] = key;
                ik2 += 1;
            }
            return true;
        }
        return false;
    }
}
