Window& reinfo();
Window& reinfo(windowsinfo& wininfo);
Window& create();
Window& create(windowscreateinfo& info);
Window& positionAdjustment(float px = 0, float py = 0);
Window& resize(float nw = 0, float nh = 0);
Window& run();
Window& close();