namespace youklx {
    void Thread::wth_vupdate() {
        int cptr = dr->cptr[dr->activeRead];
        dr->vertex.clear();
        dr->vertexptr.clear();

        if (cptr == 0) return;

        int n = wth.count;
        if (n > cptr) n = cptr;

        // 命令数太少时单线程处理以避免分发开销
        // 阈值 = 工作线程数 × 8，确保每个线程至少分到 8 条命令
        if (n <= 1 || cptr < n * 8) {
            dr->vertex.reserve(cptr * 48);
            dr->vertexptr.reserve(cptr);
            for (int i = 0; i < cptr; ++i) {
                dr->vertexptr.push_back(static_cast<int>(dr->vertex.size() / 8));
                std::visit(overloaded{
                    [this](Linecmd& cmd) {
                        auto verts = lineVertices(cmd);
                        dr->vertex.insert(dr->vertex.end(), verts.begin(), verts.end());
                    },
                    [this](Imagecmd& cmd) {
                        auto verts = imageVertices(cmd);
                        dr->vertex.insert(dr->vertex.end(), verts.begin(), verts.end());
                    },
                    [this](Fontcmd& cmd) {
                        auto verts = fontVertices(cmd);
                        dr->vertex.insert(dr->vertex.end(), verts.begin(), verts.end());
                    },
                }, dr->commands[dr->activeRead][i]);
            }
            return;
        }

        // 多线程分发：将命令均匀分配给 n 个持久化工作线程
        int mod = cptr / n;
        int emod = cptr - mod * n;
        for (int i = 0; i < n; ++i) {
            int start = i * mod + (i < emod ? i : emod);
            int end = (i + 1) * mod + ((i + 1) < emod ? (i + 1) : emod);
            if (end > cptr) end = cptr;
            wth.tasks[i].start = start;
            wth.tasks[i].end = end;
        }

        // 下一轮分发，唤醒所有工作线程
        wth.done.store(0);
        wth.gen.fetch_add(1);
        wth.cv_start.notify_all();

        // 等待所有工作线程完成
        {
            std::unique_lock<std::mutex> lock(wth.mtx);
            wth.cv_done.wait(lock, [this, n]() { return wth.done.load() >= n; });
        }

        // 按顺序合并各线程结果到 dr->vertex / dr->vertexptr
        dr->vertex.reserve(cptr * 48);
        dr->vertexptr.reserve(cptr);
        for (int i = 0; i < n; ++i) {
            int globalBase = static_cast<int>(dr->vertex.size() / 8);
            auto& task = wth.tasks[i];
            for (size_t ci = 0; ci < task.offsets.size(); ++ci) {
                dr->vertexptr.push_back(globalBase + task.offsets[ci]);
            }
            dr->vertex.insert(dr->vertex.end(), task.vertices.begin(), task.vertices.end());
        }
    }
}
