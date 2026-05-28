namespace youklx {
    Draw& Draw::image(
        Plimage img,
        float x, float y,
        float w, float h,
        float rotate, float rox, float roy,
        std::array<float,4> c1,
        std::array<float,4> c2,
        std::array<float,4> c3,
        std::array<float,4> c4
    ) {
        Imagecmd cmd;
        cmd.img = img;
        cmd.x = x; cmd.y = y;
        cmd.w = w; cmd.h = h;
        cmd.rotate = rotate; cmd.rox = rox; cmd.roy = roy;
        cmd.c1 = c1; cmd.c2 = c2;
        cmd.c3 = c3; cmd.c4 = c4;
        commands.emplace_back(cmd);
        cptr += 1;
        return *this;
    }
}