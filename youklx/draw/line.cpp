namespace youklx {
    Draw& Draw::line(
        int x1, int y1, int x2, int y2,
        float thickness,
        int rotate, int rox, int roy,
        std::array<int,2> r, std::array<int,2> g,
        std::array<int,2> b, std::array<float,2> a
    ) {
        Linecmd cmd;
        cmd.x1 = x1; cmd.y1 = y1;
        cmd.x2 = x2; cmd.y2 = y2;
        cmd.thickness = thickness;
        cmd.rotate = rotate; cmd.rox = rox; cmd.roy = roy;
        cmd.r = r;
        cmd.g = g;
        cmd.b = b;
        cmd.a = a;
        commands.emplace_back(cmd);
        cptr += 1;
        return *this;
    }
}