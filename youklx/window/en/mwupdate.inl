namespace youklx {
    void Window::mwupdate(int mx, int my) {
        w = mx;
        h = my;
        rey = static_cast<float>(h) * aspectratio;
        if (static_cast<float>(w) >= rey) {
            rex = rey;
            rey = rey / aspectratio;
            dix = (static_cast<float>(w) - rex) / 2.0f;
            diy = 0;
        } else {
            rex = static_cast<float>(w);
            rey = rex / aspectratio;
            diy = (static_cast<float>(h) - rey) / 2.0f;
            dix = 0;
        }
        reasc = static_cast<float>(rex) / static_cast<float>(mlx);
    }
}