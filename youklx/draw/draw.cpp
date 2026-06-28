namespace youklx {
    Draw::Draw() = default;

    Draw& Draw::clear() {
        commands.clear();
        cptr = 0;
        return *this;
    }
}
