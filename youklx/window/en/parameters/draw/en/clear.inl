namespace youklx {
    Draw& Draw::clear() {
        vertices.clear();
        batches.clear();
        return *this;
    }
}
