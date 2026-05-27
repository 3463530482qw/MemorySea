namespace youklx {
    Draw::Draw() {
        // 获取逻辑线程数
        nuth = std::thread::hardware_concurrency();
        if(nuth > 4) {
            nuth -= 4;
        }
    }
}