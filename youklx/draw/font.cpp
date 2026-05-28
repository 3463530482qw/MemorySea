namespace youklx {
    Draw& Draw::font(
        Font* font,
        std::string text,
        float x, float y,
        float fontSize,
        float rotate, float rox, float roy,
        std::array<float,4> rgba
    ) {
        Fontcmd cmd;
        cmd.font = font;
        cmd.text = text;
        cmd.x = x; cmd.y = y;
        cmd.fontSize = fontSize;
        cmd.rotate = rotate; cmd.rox = rox; cmd.roy = roy;
        cmd.rgba = rgba;
        commands.emplace_back(cmd);
        cptr += 1;
        return *this;
    }
}