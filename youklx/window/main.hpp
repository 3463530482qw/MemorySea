#include "parameters/create.cpp"
namespace youklx {
    class Window {
        public:
            SDL_Window* id;
            const SDL_DisplayMode *mode{nullptr};
            float aspectRatio{0};   //宽高比
            int w{0};               //窗口宽度
            int h{0};               //窗口高度
            SDL_Event pe{};         //事件
            bool isrun{true};       //是否运行

        public:
            Window() {};
            Window& init(float standardAspectRatio);
            Window& create(windowcreateinfo &exwindowcreatinfo);
            Window& positionAdjustment(int px = 0, int py = 0);
            Window& run();
        private:
    };
}
#include "init.cpp"
#include "create.cpp"
#include "positionAdjustment.cpp"
#include "run.cpp"