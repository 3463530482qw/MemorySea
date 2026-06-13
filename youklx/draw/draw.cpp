namespace youklx {
    Draw::Draw() {
    }

    Draw& Draw::clear() {
        commands.clear();
        cptr = 0;
        return *this;
    }
}
