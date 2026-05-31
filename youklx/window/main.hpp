#include "parameters/create.cpp"
#include "parameters/time.cpp"
#include "parameters/keyboard.cpp"
#include "parameters/mouse.cpp"
namespace youklx {
    class Window {
        public:
            SDL_Window* id; //窗口指针
            const SDL_DisplayMode *mode{nullptr};   //窗口句柄
            float aspectRatio{0};   //宽高比
            int w{0};               //窗口宽度
            int h{0};               //窗口高度
            int stsizew{0};         // 逻辑大小宽度
            int stsizeh{0};         // 逻辑大小高度
            SDL_Event pe{};         //事件
            bool isrun{true};       //是否运行
            Time time;              //时间相关
            Keyboard keyboard;      //键盘输入
            Mouse mouse;            //鼠标输入
        public:
            Window() {};
            Window& init(float standardAspectRatio);    //初始化窗口所需数据
            Window& iinit(std::string ini, std::string ivrtp, std::string itp);
            Window& create(windowcreateinfo &exwindowcreatinfo); //创建窗口
            Window& positionAdjustment(int px = 0, int py = 0); //设置窗口位置
            Window& run();  //运行窗口 事件处理
            Window& icon(Plimage ima);  //设置窗口图标
            Window& fps(int sfps);
            Window& ifps(std::string ini, std::string ivrtp, std::string itp);
            Window& lstsize(int w, int h); // 设置逻辑大小
            Window& ilstsize(std::string ini, std::string ivrtp, std::string witp, std::string hitp);

        private:
    };
}
#include "init.cpp"
#include "create.cpp"
#include "positionAdjustment.cpp"
#include "run.cpp"
#include "icon.cpp"
#include "fps.cpp"
#include "lstsize.cpp"
