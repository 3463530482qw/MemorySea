namespace youklx {
    Draw& Draw::line(
        Linecmd &cmd
    ) {
        commands.emplace_back(cmd);
        cptr += 1;
        return *this;
    }
}