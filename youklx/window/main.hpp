#include "parameters/init.hpp"
#include "parameters/fps.hpp"
#include "parameters/lstsize.hpp"
#include "parameters/create.cpp"
#include "parameters/time/main.hpp"
#include "parameters/key.hpp"
#include "parameters/keycode.hpp"
#include "parameters/mouse.hpp"
namespace youklx {
    class Window {
        public:
            SDL_Window* id; //窗口指针
            SDL_Window** 窗口指针{&id};
            const SDL_DisplayMode *mode{nullptr};   //窗口句柄
            float aspectRatio{0};   //宽高比
            float* 宽高比{&aspectRatio};
            int w{0};               //窗口宽度
            int* 窗口宽度{&w};
            int h{0};               //窗口高度
            int* 窗口高度{&h};
            int stsizew{0};         // 逻辑大小宽度
            int* 逻辑宽度{&stsizew};
            int stsizeh{0};         // 逻辑大小高度
            int* 逻辑高度{&stsizeh};
            // viewport 参数，由渲染线程在 drawFrame 后同步，用于鼠标坐标转换
            int viewportX{0};
            int viewportY{0};
            int viewportW{0};
            int viewportH{0};
            SDL_Event pe{};         //事件
            bool isrun{true};       //是否运行
            bool* 是否运行{&isrun};
            Time time;              //时间相关
            Keyboard key;            //键盘输入
            Mouse mouse;            //鼠标输入
        public:
            Window() {};
            Window& init(const w_init clinit);
            inline Window& 初始化(const w_init clinit) { return init(clinit); }
            Window& init(const iw_init clinit);
            inline Window& 初始化(const iw_init clinit) { return init(clinit); }
            Window& create(windowcreateinfo &exwindowcreatinfo); //创建窗口
            inline Window& 创建窗口(windowcreateinfo &exwindowcreatinfo) { return create(exwindowcreatinfo); }
            Window& positionAdjustment(int px = 0, int py = 0); //设置窗口位置
            inline Window& 调整位置(int px = 0, int py = 0) { return positionAdjustment(px, py); }
            Window& run();  //运行窗口 事件处理
            inline Window& 运行() { return run(); }
            Window& icon(Plimage ima);  //设置窗口图标
            inline Window& 设置图标(Plimage ima) { return icon(ima); }
            Window& fps(const w_fps vfps);
            inline Window& 设置帧率(const w_fps vfps) { return fps(vfps); }
            Window& fps(const iw_fps vfps);
            inline Window& 设置帧率(const iw_fps vfps) { return fps(vfps); }
            Window& lstsize(const w_lstsize vlstsize);
            inline Window& 设置逻辑大小(const w_lstsize vlstsize) { return lstsize(vlstsize); }
            Window& lstsize(const iw_lstsize vlstsize);
            inline Window& 设置逻辑大小(const iw_lstsize vlstsize) { return lstsize(vlstsize); }
        private:
            Window& pinit(const float sar);
    };
    using 窗口 = Window;
}
#include "init.cpp"
#include "create.cpp"
#include "positionAdjustment.cpp"
#include "run.cpp"
#include "icon.cpp"
#include "fps.cpp"
#include "lstsize.cpp"
#include "parameters/time/update.cpp"
#include "parameters/time/stats.cpp"
#include "parameters/time/limiter.cpp"
