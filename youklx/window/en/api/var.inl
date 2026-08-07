std::string name{"a window"};
int w{0};                         //窗口宽度
int h{0};                         //窗口高度
std::string icon;
uint8_t display_index{0};         // 显示器索引（0=主显示器）
bool isrun{true};                   // 是否运行
SDL_Window* id{nullptr};          // SDL 窗口指针
Time time;
Keyboa key;
Mouse mouse;
Wvulkan wvulkan;
Draw draw;
int mlx{1600};
int mly{900};