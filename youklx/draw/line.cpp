namespace youklx {
    Draw& Draw::line(
        Linecmd &cmd
    ) {
        commands[activeWrite].emplace_back(cmd);
        cptr[activeWrite] += 1;
        return *this;
    }

    Draw& Draw::lineBegin(int x, int y) {
        Linecmd cmd;
        cmd.from(x, y);
        commands[activeWrite].emplace_back(std::move(cmd));
        cptr[activeWrite] += 1;
        return *this;
    }

    Draw& Draw::lineTo(int x, int y) {
        if (!commands[activeWrite].empty()) {
            std::visit(overloaded{
                [x, y](Linecmd& lc) { lc.to(x, y); },
                [](auto&) {}
            }, commands[activeWrite].back());
        }
        return *this;
    }

    Draw& Draw::color(int r, int g, int b, float a) {
        if (!commands[activeWrite].empty()) {
            std::visit(overloaded{
                [r, g, b, a](Linecmd& lc) { lc.color(r, g, b, a); },
                [](auto&) {}
            }, commands[activeWrite].back());
        }
        return *this;
    }
}