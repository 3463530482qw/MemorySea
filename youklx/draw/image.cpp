namespace youklx {
    Draw& Draw::image(
        const Imagecmd &cmd
    ) {
        Imagecmd copied = cmd;
        // 从 Plpng 提取图集 UV
        if (std::holds_alternative<Plpng>(copied.img)) {
            const Plpng& png = std::get<Plpng>(copied.img);
            copied.u0 = png.u0; copied.v0 = png.v0;
            copied.u1 = png.u1; copied.v1 = png.v1;
        }

        commands.emplace_back(copied);
        cptr += 1;
        return *this;
    }
}
