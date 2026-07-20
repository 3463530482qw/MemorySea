Window& 配置() { return reinfo(); }
Window& 配置(windowsinfo& 信息) { return reinfo(信息); }
Window& 创建() { return create(); }
Window& 创建(windowscreateinfo& 信息) { return create(信息); }
Window& 调整位置(float px = 0, float py = 0) { return positionAdjustment(px, py); }
Window& 运行() { return run(); }
Window& 关闭() { return close(); }