std::string name;                 //窗口名称
int w;                            //窗口宽度
int h;                            //窗口高度
bool fullscreen{false};           // 窗口处于全屏模式
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
bool transparent{false};          // 窗口带有透明缓冲区
bool not_focusable{false};        // 窗口不应获取焦点
wininforender render;             // 窗口渲染选择                 
SDL_WindowFlags flage{0};