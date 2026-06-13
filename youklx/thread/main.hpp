namespace youklx {
    class Thread {
        public:
            Window* wi{nullptr};
            Vulkan* vk{nullptr};
            Draw* dr{nullptr};
            Image* img{nullptr};
            Font* ft{nullptr};

            int nthread{0};
            // draw 线程（执行 case 更新）
            std::thread th_draw;
            std::function<void()> draw_work;
            std::mutex mtx_draw;
            std::condition_variable cv_draw_ready;
            std::condition_variable cv_draw_done;
            bool    draw_ready{false};
            bool    draw_done{false};
            // update 线程（执行状态更新 + 渲染）
            std::thread th_update;
            std::function<void()> update_work;
            std::mutex mtx_update;
            std::condition_variable cv_update_ready;
            std::condition_variable cv_update_done;
            bool    update_ready{false};
            bool    update_done{false};
            std::atomic<bool> stopw{false};

            // 持久化工作线程池，用于分发顶点计算任务
            struct WthPool {
                std::vector<std::thread> threads;
                int count{0};
                std::atomic<int> gen{0};
                std::atomic<int> done{0};
                bool start{false};
                std::atomic<bool> stop{false};
                std::mutex mtx;
                std::condition_variable cv_start;
                std::condition_variable cv_done;
                struct Task {
                    int start, end;
                    std::vector<float> vertices;
                    std::vector<int> offsets;
                };
                std::vector<Task> tasks;
            } wth;
        public:
            Thread& init(Window& swi,Vulkan& svk,Draw& ddr,Image& img,Font& sft);
            void wth_draw(std::function<void()> work);
            void wth_update(std::function<void()> work);
            void wth_vupdate();
            ~Thread();
    };
}
#include "init.cpp"
#include "th_draw.cpp"
#include "th_update.cpp"
#include "vupdate.cpp"
#include "stop.cpp"