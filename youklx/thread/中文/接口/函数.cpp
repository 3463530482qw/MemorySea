Thread& 更新包(std::function<void()> 包体) { return update_pack(包体); }
Thread& 绘制包(std::function<void()> 包体) { return draw_pack(包体); }
Thread& 运行() { return run(); }
Thread& 包清理() { return clear(); }
