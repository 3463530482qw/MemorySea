namespace youklx {
    template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
    template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    Draw& Draw::vupdate() {
        vertex.clear();
        vertexptr.clear();

        sth.clear();
        // 开启关闭多线程计算
        if(cptr >= 50) {
            //分配命令
            mod = static_cast<float>(cptr) / static_cast<float>(nuth);
            emod = cptr - (mod * nuth);
            for (int st{0}; st <= nuth; ++st) {
                auto stth = st;
                auto ntth = nt;
                auto modth = mod;
                auto emodth = emod;
                //开启线程
                sth.emplace_back([this,stth,ntth,modth,emodth] () mutable {
                    //计算起始和结束指针
                    ntth = stth * modth;
                    if (stth == ntth) {
                        stth = ntth + emodth;
                    } else {
                        stth = ntth + modth;
                    }
                    //调度命令
                    for(;ntth <= stth; ++ntth) {
                        std::visit(overloaded{
                            [this](Linecmd& cmd) {
                                auto verts = lineVertices(cmd);
                                vertex.insert(vertex.end(), verts.begin(), verts.end());
                            },
                        }, commands[ntth]);
                    }
                });
            }
            
        } else {
            for (int i{0}; i < cptr; ++i) {
                vertexptr.push_back(static_cast<int>(vertex.size() / 6));
                std::visit(overloaded{
                    [this](Linecmd& cmd) {
                        auto verts = lineVertices(cmd);
                        vertex.insert(vertex.end(), verts.begin(), verts.end());
                    },
                }, commands[i]);
            }
        }
        for (auto& t : sth) {
            if (t.joinable()) t.join();
        }
        
        return *this;
    }
}