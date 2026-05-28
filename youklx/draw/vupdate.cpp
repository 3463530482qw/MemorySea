namespace youklx {
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    Draw& Draw::vupdate() {
        vertex.clear();
        vertexptr.clear();

        sth.clear();
        if(cptr >= 50) {
            mod = static_cast<float>(cptr) / static_cast<float>(nuth);
            emod = cptr - (mod * nuth);
            for (int st{0}; st <= nuth; ++st) {
                auto stth = st;
                auto ntth = nt;
                auto modth = mod;
                auto emodth = emod;
                sth.emplace_back([this,stth,ntth,modth,emodth] () mutable {
                    ntth = stth * modth;
                    if (stth == ntth) { stth = ntth + emodth; }
                    else { stth = ntth + modth; }
                    for(;ntth <= stth; ++ntth) {
                        std::visit(overloaded{
                            [this](Linecmd& cmd) {
                                auto verts = lineVertices(cmd);
                                vertex.insert(vertex.end(), verts.begin(), verts.end());
                            },
                            [this](Imagecmd& cmd) {
                                auto verts = imageVertices(cmd);
                                vertex.insert(vertex.end(), verts.begin(), verts.end());
                            },
                        }, commands[ntth]);
                    }
                });
            }
        } else {
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
                }, commands[i]);
            }
        }
        for (auto& t : sth) { if (t.joinable()) t.join(); }
        return *this;
    }
}