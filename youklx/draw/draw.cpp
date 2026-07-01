namespace youklx {
    Draw::Draw() = default;

    Draw& Draw::clear() {
        commands[activeRead].clear();
        cptr[activeRead] = 0;
        return *this;
    }

    void Draw::swapBuffers() {
        std::swap(activeRead, activeWrite);
    }
}
