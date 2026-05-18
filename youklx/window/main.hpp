#include "parameters/create.cpp"
namespace youklx {
    class Window {
        public:
            SDL_Window* id;
            const SDL_DisplayMode *mode{nullptr};
            float aspectRatio{0};   //宽高比
            int w{0};               //窗口宽度
            int h{0};               //窗口高度
        public:
            Window() {};
            void init(float standardAspectRatio);
            void create(windowcreateinfo &exwindowcreatinfo);
        private:
    };
}
#include "init.cpp"
#include "create.cpp"