namespace youklx {
    class windowcreateinfo {
    public:
        std::string name;                 //窗口名称
        int w;                            //窗口宽度
        int h;                            //窗口高度
        bool fullscreen{false};           // 窗口处于全屏模式
        bool opengl{false};               // 窗口可用于 OpenGL 上下文
        bool occluded{false};             // 窗口被遮挡
        bool hidden{false};               // 窗口隐藏，不在桌面映射且不显示在任务栏
        bool borderless{false};           // 无边框窗口（无窗口装饰）
        bool resizable{false};            // 窗口可调整大小
        bool minimized{false};            // 窗口已最小化
        bool maximized{false};            // 窗口已最大化
        bool mouse_grabbed{false};        // 窗口捕获（抓取）了鼠标输入
        bool input_focus{false};          // 窗口拥有输入焦点
        bool mouse_focus{false};          // 窗口拥有鼠标焦点
        bool external{false};             // 窗口并非由 SDL 创建（外部窗口）
        bool modal{false};                // 窗口为模态窗口
        bool high_pixel_density{false};   // 窗口尽可能使用高像素密度后端缓冲区
        bool mouse_capture{false};        // 窗口捕获了鼠标（与mouse_grabbed无关）
        bool mouse_relative_mode{false};  // 窗口启用了鼠标相对模式
        bool always_on_top{false};        // 窗口始终置于最顶层
        bool utility{false};              // 窗口作为实用工具窗口，不显示在任务栏和窗口列表中
        bool tooltip{false};              // 窗口作为工具提示，不获取鼠标/键盘焦点，需要父窗口
        bool popup_menu{false};           // 窗口作为弹出菜单，需要父窗口
        bool keyboard_grabbed{false};     // 窗口捕获（抓取）了键盘输入
        bool fill_document{false};        // 窗口处于填充文档模式（仅限Emscripten）
        bool vulkan{false};               // 窗口可用于 Vulkan 渲染表面
        bool metal{false};                // 窗口可用于 Metal 渲染视图
        bool transparent{false};          // 窗口带有透明缓冲区
        bool not_focusable{false};        // 窗口不应获取焦点
        SDL_WindowFlags flage{0};
    public:
        windowcreateinfo& ffullscreen(bool exfullscreen) { fullscreen = exfullscreen; return *this; }; 
        windowcreateinfo& fopengl(bool exopengl) { opengl = exopengl; return *this; }
        windowcreateinfo& foccluded(bool exoccluded) { occluded = exoccluded; return *this; }
        windowcreateinfo& fhidden(bool exhidden) { hidden = exhidden; return *this; }
        windowcreateinfo& fborderless(bool exborderless) { borderless = exborderless; return *this; }
        windowcreateinfo& fresizable(bool exresizable) { resizable = exresizable; return *this; }
        windowcreateinfo& fminimized(bool exminimized) { minimized = exminimized; return *this; }
        windowcreateinfo& fmaximized(bool exmaximized) { maximized = exmaximized; return *this; }
        windowcreateinfo& fmouse_grabbed(bool exmouse_grabbed) { mouse_grabbed = exmouse_grabbed; return *this; }
        windowcreateinfo& finput_focus(bool exinput_focus) { input_focus = exinput_focus; return *this; }
        windowcreateinfo& fmouse_focus(bool exmouse_focus) { mouse_focus = exmouse_focus; return *this; }
        windowcreateinfo& fexternal(bool exexternal) { external = exexternal; return *this; }
        windowcreateinfo& fmodal(bool exmodal) { modal = exmodal; return *this; }
        windowcreateinfo& fhigh_pixel_density(bool exhigh_pixel_density) { high_pixel_density = exhigh_pixel_density; return *this; }
        windowcreateinfo& fmouse_capture(bool exmouse_capture) { mouse_capture = exmouse_capture; return *this; }
        windowcreateinfo& fmouse_relative_mode(bool exmouse_relative_mode) { mouse_relative_mode = exmouse_relative_mode; return *this; }
        windowcreateinfo& falways_on_top(bool exalways_on_top) { always_on_top = exalways_on_top; return *this; }
        windowcreateinfo& futility(bool exutility) { utility = exutility; return *this; }
        windowcreateinfo& ftooltip(bool extooltip) { tooltip = extooltip; return *this; }
        windowcreateinfo& fpopup_menu(bool expopup_menu) { popup_menu = expopup_menu; return *this; }
        windowcreateinfo& fkeyboard_grabbed(bool exkeyboard_grabbed) { keyboard_grabbed = exkeyboard_grabbed; return *this; }
        windowcreateinfo& ffill_document(bool exfill_document) { fill_document = exfill_document; return *this; }
        windowcreateinfo& fvulkan(bool exvulkan) { vulkan = exvulkan; return *this; }
        windowcreateinfo& fmetal(bool exmetal) { metal = exmetal; return *this; }
        windowcreateinfo& ftransparent(bool extransparent) { transparent = extransparent; return *this; }
        windowcreateinfo& fnot_focusable(bool exnot_focusable) { not_focusable = exnot_focusable; return *this; }
        
        windowcreateinfo& loadini(std::string ini) {
            INIReader reader(ini);
            if (reader.ParseError() != 0) {
                std::cerr << "Configuration load failed, using default configuration" << std::endl;
            }
            name = reader.Get("windowcreate", "name", "a window");
            w = reader.GetInteger("windowcreate", "w", 0);
            h = reader.GetInteger("windowcreate", "h", 0);
            fullscreen          = reader.GetBoolean("windowcreate", "fullscreen", false);
            opengl              = reader.GetBoolean("windowcreate", "opengl", false);
            occluded            = reader.GetBoolean("windowcreate", "occluded", false);
            hidden              = reader.GetBoolean("windowcreate", "hidden", false);
            borderless          = reader.GetBoolean("windowcreate", "borderless", false);
            resizable           = reader.GetBoolean("windowcreate", "resizable", false);
            minimized           = reader.GetBoolean("windowcreate", "minimized", false);
            maximized           = reader.GetBoolean("windowcreate", "maximized", false);
            mouse_grabbed       = reader.GetBoolean("windowcreate", "mouse_grabbed", false);
            input_focus         = reader.GetBoolean("windowcreate", "input_focus", false);
            mouse_focus         = reader.GetBoolean("windowcreate", "mouse_focus", false);
            external            = reader.GetBoolean("windowcreate", "external", false);
            modal               = reader.GetBoolean("windowcreate", "modal", false);
            high_pixel_density  = reader.GetBoolean("windowcreate", "high_pixel_density", false);
            mouse_capture       = reader.GetBoolean("windowcreate", "mouse_capture", false);
            mouse_relative_mode = reader.GetBoolean("windowcreate", "mouse_relative_mode", false);
            always_on_top       = reader.GetBoolean("windowcreate", "always_on_top", false);
            utility             = reader.GetBoolean("windowcreate", "utility", false);
            tooltip             = reader.GetBoolean("windowcreate", "tooltip", false);
            popup_menu          = reader.GetBoolean("windowcreate", "popup_menu", false);
            keyboard_grabbed    = reader.GetBoolean("windowcreate", "keyboard_grabbed", false);
            fill_document       = reader.GetBoolean("windowcreate", "fill_document", false);
            vulkan              = reader.GetBoolean("windowcreate", "vulkan", false);
            metal               = reader.GetBoolean("windowcreate", "metal", false);
            transparent         = reader.GetBoolean("windowcreate", "transparent", false);
            not_focusable       = reader.GetBoolean("windowcreate", "not_focusable", false);
            return *this;
        }
        void load() {
            flage = static_cast<SDL_WindowFlags>(0);
            if (fullscreen)          flage |= SDL_WINDOW_FULLSCREEN;
            if (opengl)              flage |= SDL_WINDOW_OPENGL;
            if (occluded)            flage |= SDL_WINDOW_OCCLUDED;
            if (hidden)              flage |= SDL_WINDOW_HIDDEN;
            if (borderless)          flage |= SDL_WINDOW_BORDERLESS;
            if (resizable)           flage |= SDL_WINDOW_RESIZABLE;
            if (minimized)           flage |= SDL_WINDOW_MINIMIZED;
            if (maximized)           flage |= SDL_WINDOW_MAXIMIZED;
            if (mouse_grabbed)       flage |= SDL_WINDOW_MOUSE_GRABBED;
            if (input_focus)         flage |= SDL_WINDOW_INPUT_FOCUS;
            if (mouse_focus)         flage |= SDL_WINDOW_MOUSE_FOCUS;
            if (external)            flage |= SDL_WINDOW_EXTERNAL;
            if (modal)               flage |= SDL_WINDOW_MODAL;
            if (high_pixel_density)  flage |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
            if (mouse_capture)       flage |= SDL_WINDOW_MOUSE_CAPTURE;
            if (mouse_relative_mode) flage |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
            if (always_on_top)       flage |= SDL_WINDOW_ALWAYS_ON_TOP;
            if (utility)             flage |= SDL_WINDOW_UTILITY;
            if (tooltip)             flage |= SDL_WINDOW_TOOLTIP;
            if (popup_menu)          flage |= SDL_WINDOW_POPUP_MENU;
            if (keyboard_grabbed)    flage |= SDL_WINDOW_KEYBOARD_GRABBED;
            if (fill_document)       flage |= SDL_WINDOW_FILL_DOCUMENT;
            if (vulkan)              flage |= SDL_WINDOW_VULKAN;
            if (metal)               flage |= SDL_WINDOW_METAL;
            if (transparent)         flage |= SDL_WINDOW_TRANSPARENT;
            if (not_focusable)       flage |= SDL_WINDOW_NOT_FOCUSABLE;
        }
    };
}
