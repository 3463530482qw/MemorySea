std::vector<SDL_DisplayID> displays;
SDL_Window* id{nullptr};          // SDL 窗口指针
SDL_WindowID wid{0};
SDL_Event pept;                       // 窗口事件
std::vector<SDL_Event> pe;
const SDL_DisplayMode* mode{nullptr};  // 当前显示器模式（SDL_GetCurrentDisplayMode 返回 const）