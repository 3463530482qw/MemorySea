namespace youklx {
    Draw::Draw() {
        // 获取逻辑线程数，最少保留 1 个线程防止除零
        nuth = std::max(1u, std::thread::hardware_concurrency());
        if(nuth > 4) {
            nuth -= 4;
        }
        if(nuth < 1) nuth = 1;
    }

    Draw& Draw::clear() {
        commands.clear();
        cptr = 0;
        return *this;
    }
}