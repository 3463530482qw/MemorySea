namespace youklx {
    Draw& Draw::vupdate() {
        vertex.clear();
        vertexptr.clear();
        vertex.reserve(cptr * 48);
        vertexptr.reserve(cptr);

        for (int i{0}; i < cptr; ++i) {
            vertexptr.push_back(static_cast<int>(vertex.size() / 8));
            std::visit(overloaded{
                [this](Linecmd& cmd) {
                    auto verts = lineVertices(cmd);
                    vertex.insert(vertex.end(), verts.begin(), verts.end());
                },
                [this](Imagecmd& cmd) {
                    auto verts = imageVertices(cmd);
                    vertex.insert(vertex.end(), verts.begin(), verts.end());
                },
                [this](Fontcmd& cmd) {
                    auto verts = fontVertices(cmd);
                    vertex.insert(vertex.end(), verts.begin(), verts.end());
                },
            }, commands[i]);
        }
        return *this;
    }
}
