uint8_t nths;
std::mutex mtx;
std::condition_variable cv;
std::array<std::jthread, mnths> th_pool;
// 永久任务注册表
std::vector<std::function<void()>> update_tasks;
std::vector<std::function<void()>> draw_tasks;
// 任务级追踪：claimed(已认领) / 防止索引越界自旋
std::atomic<size_t> update_claimed{0};
std::atomic<size_t> draw_claimed{0};
std::atomic<size_t> update_completed{0};
std::atomic<size_t> draw_completed{0};
std::atomic<bool> update_done{true};
std::atomic<bool> draw_done{true};
