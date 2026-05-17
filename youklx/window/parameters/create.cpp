namespace youklx {
    class windowcreateinfo {
        public:
            std::string wname{"a window"};  //窗口名称
            int width{0};                   // 窗口宽度
            int height{0};                  // 窗口高度
            bool wnoborder{false};           // 无边框
            bool wnoresize{false};           // 禁止调整大小
            bool wallowdnd{false};           // 允许拖放文件
            bool whidemouse{false};          // 隐藏鼠标光标
            bool wfullscreen{false};         // 独占全屏模式
            bool wtransparent{false};        // 窗口透明
            bool wcenter{false};             // 在屏幕居中显示
            bool wscaletomonitor{false};     // 根据显示器DPI缩放
            bool whide{false};               // 创建时隐藏窗口
            bool wmaximize{false};           // 创建时最大化
            bool wcentercursor{false};       // 创建时将光标居中于窗口
            bool wfloating{false};           // 窗口始终置顶（浮动）
            bool wfocusonshow{false};        // 显示窗口时自动获取焦点
            bool wminimize{false};           // 创建时最小化
            bool wfocus{false};              // 创建时获取输入焦点
            bool wopengl{false};             // 创建OpenGL上下文
            bool wegl{false};                // 创建EGL上下文
            bool wwindowedfullscreen{false}; // 窗口化全屏（无边框+最大化）



        public:
            windowcreateinfo& name(std::string exname) { wname = exname; return *this; };
            windowcreateinfo& w(int exwidth) { width = exwidth; return *this; };
            windowcreateinfo& h(int exheight) { height = exheight; return *this; };
            windowcreateinfo& noborder(bool exnoborder) { wnoborder = exnoborder; return *this; };
            windowcreateinfo& noresize(bool exnoresize) { wnoresize = exnoresize; return *this; };
            windowcreateinfo& allowdnd(bool exallowdnd) { wallowdnd = exallowdnd; return *this; };
            windowcreateinfo& hidemouse(bool exhidemouse) { whidemouse = exhidemouse; return *this; };
            windowcreateinfo& fullscreen(bool exfullscreen) { wfullscreen = exfullscreen; return *this; };
            windowcreateinfo& transparent(bool extransparent) { wtransparent = extransparent; return *this; };
            windowcreateinfo& center(bool excenter) { wcenter = excenter; return *this; };
            windowcreateinfo& scaletomonitor(bool exscaletomonitor) { wscaletomonitor = exscaletomonitor; return *this; };
            windowcreateinfo& hide(bool exhide) { whide = exhide; return *this; };
            windowcreateinfo& maximize(bool exmaximize) { wmaximize = exmaximize; return *this; };
            windowcreateinfo& centercursor(bool excentercursor) { wcentercursor = excentercursor; return *this; };
            windowcreateinfo& floating(bool exfloating) { wfloating = exfloating; return *this; };
            windowcreateinfo& focusonshow(bool exfocusonshow) { wfocusonshow = exfocusonshow; return *this; };
            windowcreateinfo& minimize(bool exminimize) { wminimize = exminimize; return *this; };
            windowcreateinfo& focus(bool exfocus) { wfocus = exfocus; return *this; };
            windowcreateinfo& opengl(bool exopengl) { wopengl = exopengl; return *this; };
            windowcreateinfo& egl(bool exegl) { wegl = exegl; return *this; };
            windowcreateinfo& windowedfullscreen(bool exwindowedfullscreen) { wwindowedfullscreen = exwindowedfullscreen; return *this; };
    };
}
