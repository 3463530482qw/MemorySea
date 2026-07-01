namespace youklx {
    Thread& Thread::init(Window& swi,Vulkan& svk,Draw& sdr,Image& simg,Font& sft) {
        wi = &swi;
        vk = &svk;
        dr = &sdr;
        img = &simg;
        ft = &sft;
        int hcount = std::thread::hardware_concurrency();
        // 为更新/绘制线程预留 2 核，工作池取剩余核心，下限 2
        nthread = std::max(2, hcount - 2);

        // 创建持久化工作线程池，每个线程等待顶点计算任务分发
        wth.count = nthread;
        wth.tasks.resize(nthread);
        for (int i = 0; i < nthread; ++i) {
            wth.threads.emplace_back([this, i]() {
                int my_gen = 0;
                while (true) {
                    {
                        std::unique_lock<std::mutex> lock(wth.mtx);
                        wth.cv_start.wait(lock, [this, &my_gen]() {
                            return wth.stop || wth.gen.load() > my_gen;
                        });
                        if (wth.stop) return;
                        my_gen = wth.gen.load();
                    }
                    // 执行分配的任务
                    auto& task = wth.tasks[i];
                    task.vertices.clear();
                    task.offsets.clear();
                    task.offsets.reserve(task.end - task.start);
                    task.vertices.reserve((task.end - task.start) * 48);
                    for (int n = task.start; n < task.end; ++n) {
                        task.offsets.push_back(static_cast<int>(task.vertices.size() / 8));
                        std::visit(overloaded{
                            [&task](Linecmd& cmd) {
                                auto verts = lineVertices(cmd);
                                task.vertices.insert(task.vertices.end(), verts.begin(), verts.end());
                            },
                            [&task](Imagecmd& cmd) {
                                auto verts = imageVertices(cmd);
                                task.vertices.insert(task.vertices.end(), verts.begin(), verts.end());
                            },
                            [&task](Fontcmd& cmd) {
                                auto verts = fontVertices(cmd);
                                task.vertices.insert(task.vertices.end(), verts.begin(), verts.end());
                            },
                        }, dr->commands[dr->activeRead][n]);
                    }
                    // 仅最后一个完成的工作线程通知主线程
                    if (wth.done.fetch_add(1) == wth.count - 1)
                        wth.cv_done.notify_one();
                }
            });
            // 工作线程优先级低于关键路径，避免抢占更新/绘制线程
            #ifdef _WIN32
            SetThreadPriority(wth.threads.back().native_handle(), THREAD_PRIORITY_BELOW_NORMAL);
            #endif
        }
        return *this;
    }
}