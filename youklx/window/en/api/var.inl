std::vector<SDL_DisplayID> displays;
SDL_Window* id{nullptr};          // SDL 窗口指针
std::string name{"a window"};
int w{0};                         //窗口宽度
int h{0};                         //窗口高度
uint8_t display_index{0};         // 显示器索引（0=主显示器）
const SDL_DisplayMode* mode{nullptr};
