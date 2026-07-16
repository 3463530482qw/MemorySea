// 基本属性
std::string& 名称{name};
int& 宽{w};         
int& 高{h};    

// 窗口标志 — 中文引用别名
bool& 全屏{fullscreen};
bool& 被遮挡{occluded};
bool& 隐藏{hidden};
bool& 无边框{borderless};
bool& 可调大小{resizable};
bool& 已最小化{minimized};
bool& 已最大化{maximized};
bool& 鼠标抓取{mouse_grabbed};
bool& 输入焦点{input_focus};
bool& 鼠标焦点{mouse_focus};
bool& 外部窗口{external};
bool& 模态{modal};
bool& 高像素密度{high_pixel_density};
bool& 鼠标捕获{mouse_capture};
bool& 鼠标相对模式{mouse_relative_mode};
bool& 始终置顶{always_on_top};
bool& 实用工具{utility};
bool& 工具提示{tooltip};
bool& 弹出菜单{popup_menu};
bool& 键盘抓取{keyboard_grabbed};
bool& 填充文档{fill_document};
bool& 透明{transparent};
bool& 不可聚焦{not_focusable};

// 渲染接口
wininforender& 渲染接口{render};

// 原始 SDL 标志位
SDL_WindowFlags flage{0};  