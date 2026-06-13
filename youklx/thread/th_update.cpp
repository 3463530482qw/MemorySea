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
                    dr->vupdate();
                    vk->updateTexture(*img);
                    vk->updateFontTexture(ft);
                    vk->updateVertexBuffer(dr->vertex);
                    vk->drawFrame(*dr);
                    // 将 viewport 参数同步到 Window，供 run() 中鼠标坐标转换使用
                    wi->viewportX = vk->viewportX;
                    wi->viewportY = vk->viewportY;
                    wi->viewportW = vk->viewportW;
                    wi->viewportH = vk->viewportH;
                    dr->clear();

                    {
                        std::lock_guard<std::mutex> lock(mtx_update);
                        update_done = true;
                        update_ready = false;
                    }
                    cv_update_done.notify_one();
                }
            });
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