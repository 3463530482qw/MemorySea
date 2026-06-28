namespace youklx {
    Draw& Draw::line(
        Linecmd &cmd
    ) {
        commands.emplace_back(cmd);
        cptr += 1;
        return *this;
    }

    Draw& Draw::lineBegin(int x, int y) {
        Linecmd cmd;
        cmd.from(x, y);
        commands.emplace_back(std::move(cmd));
        cptr += 1;
        return *this;
    }

    Draw& Draw::lineTo(int x, int y) {
        if (!commands.empty()) {
            std::visit(overloaded{
                [x, y](Linecmd& lc) { lc.to(x, y); },
                [](auto&) {}
            }, commands.back());
        }
        return *this;
    }

    Draw& Draw::color(int r, int g, int b, float a) {
        if (!commands.empty()) {
            std::visit(overloaded{
                [r, g, b, a](Linecmd& lc) { lc.color(r, g, b, a); },
                [](auto&) {}
            }, commands.back());
        }
        return *this;
    }
}