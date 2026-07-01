namespace youklx {
    void Thread::wth_update(std::function<void()> work) {
        if (!th_update.joinable()) {
            th_update = std::thread([this]() {
                while (true) {
                    {
                        std::unique_lock<std::mutex> lock(mtx_update);
                        cv_update_ready.wait(lock, [this]() { return update_ready || stopw; });
                        if (stopw) return;
                    }

                    wi->time.update();
                    update_work();

                    // 触发绘制线程 — 写缓冲与读缓冲分离，可与 vupdate 并行
                    if (draw_work_stored) {
                        {
                            std::lock_guard<std::mutex> lock(mtx_draw);
                            draw_ready = true;
                            draw_done = false;
                        }
                        cv_draw_ready.notify_one();
                    }

                    // 首帧（读缓冲为空）必须等绘制完成再 vupdate
                    bool drawWaited = false;
                    if (draw_work_stored && dr->cptr[dr->activeRead] == 0) {
                        {
                            std::unique_lock<std::mutex> lock(mtx_draw);
                            cv_draw_done.wait(lock, [this]() { return draw_done; });
                        }
                        drawWaited = true;
                    }

                    // vupdate 读缓冲 + GPU 渲染（与绘制线程写缓冲并行）
                    wth_vupdate();
                    vk->updateTexture(*img);
                    vk->updateFontTexture(ft);
                    vk->updateVertexBuffer(dr->vertex);
                    vk->drawFrame(*dr);
                    // 将 viewport 参数同步到 Window，供 run() 中鼠标坐标转换使用
                    wi->viewportX = vk->viewportX;
                    wi->viewportY = vk->viewportY;
                    wi->viewportW = vk->viewportW;
                    wi->viewportH = vk->viewportH;

                    // 常规帧 — vupdate 完成后等待绘制，然后 swap
                    if (draw_work_stored && !drawWaited) {
                        {
                            std::unique_lock<std::mutex> lock(mtx_draw);
                            cv_draw_done.wait(lock, [this]() { return draw_done; });
                        }
                    }

                    if (draw_work_stored) {
                        draw_work_stored = false;
                        dr->clear();       // 清空已消费的读缓冲
                        dr->swapBuffers(); // 交换读写角色：写缓冲 → 下帧可用
                    }

                    {
                        std::lock_guard<std::mutex> lock(mtx_update);
                        update_done = true;
                        update_ready = false;
                    }
                    cv_update_done.notify_one();
                }
            });
            // 更新线程优先级最高：驱动帧循环，不能被其他线程抢占
            #ifdef _WIN32
            SetThreadPriority(th_update.native_handle(), THREAD_PRIORITY_ABOVE_NORMAL);
            #endif
        }

        update_work = std::move(work);

        {
            std::lock_guard<std::mutex> lock(mtx_update);
            update_ready = true;
            update_done = false;
        }
        cv_update_ready.notify_one();

        {
            std::unique_lock<std::mutex> lock(mtx_update);
            cv_update_done.wait(lock, [this]() { return update_done; });
        }
    }
}