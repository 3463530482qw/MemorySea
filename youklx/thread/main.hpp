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
            bool    stopw{false};
        public:
            Thread& init(Window& swi,Vulkan& svk,Draw& ddr,Image& img,Font& sft);
            void wth_draw(std::function<void()> work);
            void wth_update(std::function<void()> work);
    };
}
#include "init.cpp"
#include "th_draw.cpp"
#include "th_update.cpp"