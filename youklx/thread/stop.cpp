namespace youklx {
    Thread::~Thread() {
        stopw = true;
        wth.stop = true;

        // 唤醒 draw 线程使其退出
        {
            std::lock_guard<std::mutex> lock(mtx_draw);
            draw_ready = true;
        }
        cv_draw_ready.notify_one();

        // 唤醒 update 线程使其退出
        {
            std::lock_guard<std::mutex> lock(mtx_update);
            update_ready = true;
        }
        cv_update_ready.notify_one();

        // 唤醒所有工作线程使其退出
        {
            std::lock_guard<std::mutex> lock(wth.mtx);
            wth.start = true;
        }
        wth.cv_start.notify_all();

        // 等待所有线程结束
        if (th_draw.joinable()) th_draw.join();
        if (th_update.joinable()) th_update.join();
        for (auto& t : wth.threads) {
            if (t.joinable()) t.join();
        }
    }
}
