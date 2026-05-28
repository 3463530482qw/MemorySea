namespace youklx {
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    Draw& Draw::vupdate() {
        vertex.clear();
        vertexptr.clear();

        sth.clear();
        if(cptr >= 50) {
            mod = static_cast<float>(cptr) / static_cast<float>(nuth);
            emod = cptr - static_cast<int>(mod * nuth);
            // 每个线程使用独立的局部缓冲区和局部偏移表，避免数据竞争
            struct ThreadResult {
                std::vector<float> vertices;
                std::vector<int> offsets; // 每条命令的起始顶点索引（局部，以 8 浮点数为单位）
            };
            std::vector<ThreadResult> threadResults(nuth + 1);
            for (int st{0}; st <= nuth; ++st) {
                auto stth = st;
                auto modth = mod;
                auto emodth = emod;
                sth.emplace_back([this,stth,modth,emodth,&threadResults] () {
                    int start = stth * static_cast<int>(modth);
                    if (stth < emodth) start += stth;
                    else start += emodth;
                    int end = (stth + 1) * static_cast<int>(modth);
                    if ((stth + 1) < emodth) end += (stth + 1);
                    else end += emodth;
                    if (end > cptr) end = cptr;
                    for (int n = start; n < end; ++n) {
                        threadResults[stth].offsets.push_back(static_cast<int>(threadResults[stth].vertices.size() / 8));
                        std::visit(overloaded{
                            [&threadResults,stth](Linecmd& cmd) {
                                auto verts = lineVertices(cmd);
                                threadResults[stth].vertices.insert(threadResults[stth].vertices.end(), verts.begin(), verts.end());
                            },
                            [&threadResults,stth](Imagecmd& cmd) {
                                auto verts = imageVertices(cmd);
                                threadResults[stth].vertices.insert(threadResults[stth].vertices.end(), verts.begin(), verts.end());
                            },
                            [&threadResults,stth](Fontcmd& cmd) {
                                auto verts = fontVertices(cmd);
                                threadResults[stth].vertices.insert(threadResults[stth].vertices.end(), verts.begin(), verts.end());
                            },
                        }, commands[n]);
                    }
                });
            }
            for (auto& t : sth) { if (t.joinable()) t.join(); }
            // 按命令顺序合并：每个线程处理的命令是连续的，依次拼接
            for (int st{0}; st <= nuth; ++st) {
                int globalBase = static_cast<int>(vertex.size() / 8);
                for (size_t ci = 0; ci < threadResults[st].offsets.size(); ++ci) {
                    vertexptr.push_back(globalBase + threadResults[st].offsets[ci]);
                }
                vertex.insert(vertex.end(),
                    threadResults[st].vertices.begin(),
                    threadResults[st].vertices.end());
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
                    [this](Fontcmd& cmd) {
                        auto verts = fontVertices(cmd);
                        vertex.insert(vertex.end(), verts.begin(), verts.end());
                    },
                }, commands[i]);
            }
        }
        return *this;
    }
}
