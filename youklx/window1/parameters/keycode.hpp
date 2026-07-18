namespace youklx {

// ============================
//  字母键 A-Z
// ============================
inline constexpr SDL_Keycode ky_a = SDLK_A;
inline constexpr SDL_Keycode ky_b = SDLK_B;
inline constexpr SDL_Keycode ky_c = SDLK_C;
inline constexpr SDL_Keycode ky_d = SDLK_D;
inline constexpr SDL_Keycode ky_e = SDLK_E;
inline constexpr SDL_Keycode ky_f = SDLK_F;
inline constexpr SDL_Keycode ky_g = SDLK_G;
inline constexpr SDL_Keycode ky_h = SDLK_H;
inline constexpr SDL_Keycode ky_i = SDLK_I;
inline constexpr SDL_Keycode ky_j = SDLK_J;
inline constexpr SDL_Keycode ky_k = SDLK_K;
inline constexpr SDL_Keycode ky_l = SDLK_L;
inline constexpr SDL_Keycode ky_m = SDLK_M;
inline constexpr SDL_Keycode ky_n = SDLK_N;
inline constexpr SDL_Keycode ky_o = SDLK_O;
inline constexpr SDL_Keycode ky_p = SDLK_P;
inline constexpr SDL_Keycode ky_q = SDLK_Q;
inline constexpr SDL_Keycode ky_r = SDLK_R;
inline constexpr SDL_Keycode ky_s = SDLK_S;
inline constexpr SDL_Keycode ky_t = SDLK_T;
inline constexpr SDL_Keycode ky_u = SDLK_U;
inline constexpr SDL_Keycode ky_v = SDLK_V;
inline constexpr SDL_Keycode ky_w = SDLK_W;
inline constexpr SDL_Keycode ky_x = SDLK_X;
inline constexpr SDL_Keycode ky_y = SDLK_Y;
inline constexpr SDL_Keycode ky_z = SDLK_Z;

// ============================
//  数字键 0-9
// ============================
inline constexpr SDL_Keycode ky_0 = SDLK_0;
inline constexpr SDL_Keycode ky_1 = SDLK_1;
inline constexpr SDL_Keycode ky_2 = SDLK_2;
inline constexpr SDL_Keycode ky_3 = SDLK_3;
inline constexpr SDL_Keycode ky_4 = SDLK_4;
inline constexpr SDL_Keycode ky_5 = SDLK_5;
inline constexpr SDL_Keycode ky_6 = SDLK_6;
inline constexpr SDL_Keycode ky_7 = SDLK_7;
inline constexpr SDL_Keycode ky_8 = SDLK_8;
inline constexpr SDL_Keycode ky_9 = SDLK_9;

// ============================
//  功能键 F1-F12
// ============================
inline constexpr SDL_Keycode ky_f1  = SDLK_F1;
inline constexpr SDL_Keycode ky_f2  = SDLK_F2;
inline constexpr SDL_Keycode ky_f3  = SDLK_F3;
inline constexpr SDL_Keycode ky_f4  = SDLK_F4;
inline constexpr SDL_Keycode ky_f5  = SDLK_F5;
inline constexpr SDL_Keycode ky_f6  = SDLK_F6;
inline constexpr SDL_Keycode ky_f7  = SDLK_F7;
inline constexpr SDL_Keycode ky_f8  = SDLK_F8;
inline constexpr SDL_Keycode ky_f9  = SDLK_F9;
inline constexpr SDL_Keycode ky_f10 = SDLK_F10;
inline constexpr SDL_Keycode ky_f11 = SDLK_F11;
inline constexpr SDL_Keycode ky_f12 = SDLK_F12;

// ============================
//  方向键
// ============================
inline constexpr SDL_Keycode ky_up    = SDLK_UP;
inline constexpr SDL_Keycode ky_down  = SDLK_DOWN;
inline constexpr SDL_Keycode ky_left  = SDLK_LEFT;
inline constexpr SDL_Keycode ky_right = SDLK_RIGHT;

// ============================
//  常用编辑/控制键
// ============================
inline constexpr SDL_Keycode ky_return    = SDLK_RETURN;
inline constexpr SDL_Keycode ky_escape    = SDLK_ESCAPE;
inline constexpr SDL_Keycode ky_backspace = SDLK_BACKSPACE;
inline constexpr SDL_Keycode ky_tab       = SDLK_TAB;
inline constexpr SDL_Keycode ky_space     = SDLK_SPACE;
inline constexpr SDL_Keycode ky_delete    = SDLK_DELETE;
inline constexpr SDL_Keycode ky_insert    = SDLK_INSERT;
inline constexpr SDL_Keycode ky_home      = SDLK_HOME;
inline constexpr SDL_Keycode ky_end       = SDLK_END;
inline constexpr SDL_Keycode ky_pageup    = SDLK_PAGEUP;
inline constexpr SDL_Keycode ky_pagedown  = SDLK_PAGEDOWN;

// ============================
//  修饰键
// ============================
inline constexpr SDL_Keycode ky_lctrl  = SDLK_LCTRL;
inline constexpr SDL_Keycode ky_lshift = SDLK_LSHIFT;
inline constexpr SDL_Keycode ky_lalt   = SDLK_LALT;
inline constexpr SDL_Keycode ky_lgui   = SDLK_LGUI;
inline constexpr SDL_Keycode ky_rctrl  = SDLK_RCTRL;
inline constexpr SDL_Keycode ky_rshift = SDLK_RSHIFT;
inline constexpr SDL_Keycode ky_ralt   = SDLK_RALT;
inline constexpr SDL_Keycode ky_rgui   = SDLK_RGUI;

// ============================
//  锁定键
// ============================
inline constexpr SDL_Keycode ky_capslock   = SDLK_CAPSLOCK;
inline constexpr SDL_Keycode ky_numlock    = SDLK_NUMLOCKCLEAR;
inline constexpr SDL_Keycode ky_scrolllock = SDLK_SCROLLLOCK;

// ============================
//  其它键
// ============================
inline constexpr SDL_Keycode ky_printscreen = SDLK_PRINTSCREEN;
inline constexpr SDL_Keycode ky_pause       = SDLK_PAUSE;

// ============================
//  符号键
// ============================
inline constexpr SDL_Keycode ky_minus        = SDLK_MINUS;
inline constexpr SDL_Keycode ky_equals       = SDLK_EQUALS;
inline constexpr SDL_Keycode ky_leftbracket  = SDLK_LEFTBRACKET;
inline constexpr SDL_Keycode ky_rightbracket = SDLK_RIGHTBRACKET;
inline constexpr SDL_Keycode ky_backslash    = SDLK_BACKSLASH;
inline constexpr SDL_Keycode ky_semicolon    = SDLK_SEMICOLON;
inline constexpr SDL_Keycode ky_apostrophe   = SDLK_APOSTROPHE;
inline constexpr SDL_Keycode ky_comma        = SDLK_COMMA;
inline constexpr SDL_Keycode ky_period       = SDLK_PERIOD;
inline constexpr SDL_Keycode ky_slash        = SDLK_SLASH;
inline constexpr SDL_Keycode ky_grave        = SDLK_GRAVE;

// ============================
//  小键盘
// ============================
inline constexpr SDL_Keycode ky_kp_0        = SDLK_KP_0;
inline constexpr SDL_Keycode ky_kp_1        = SDLK_KP_1;
inline constexpr SDL_Keycode ky_kp_2        = SDLK_KP_2;
inline constexpr SDL_Keycode ky_kp_3        = SDLK_KP_3;
inline constexpr SDL_Keycode ky_kp_4        = SDLK_KP_4;
inline constexpr SDL_Keycode ky_kp_5        = SDLK_KP_5;
inline constexpr SDL_Keycode ky_kp_6        = SDLK_KP_6;
inline constexpr SDL_Keycode ky_kp_7        = SDLK_KP_7;
inline constexpr SDL_Keycode ky_kp_8        = SDLK_KP_8;
inline constexpr SDL_Keycode ky_kp_9        = SDLK_KP_9;
inline constexpr SDL_Keycode ky_kp_period   = SDLK_KP_PERIOD;
inline constexpr SDL_Keycode ky_kp_divide   = SDLK_KP_DIVIDE;
inline constexpr SDL_Keycode ky_kp_multiply = SDLK_KP_MULTIPLY;
inline constexpr SDL_Keycode ky_kp_minus    = SDLK_KP_MINUS;
inline constexpr SDL_Keycode ky_kp_plus     = SDLK_KP_PLUS;
inline constexpr SDL_Keycode ky_kp_enter    = SDLK_KP_ENTER;
inline constexpr SDL_Keycode ky_kp_equals   = SDLK_KP_EQUALS;

// ============================
//  中文别名 — 字母键
// ============================
inline constexpr SDL_Keycode 键_a = SDLK_A;
inline constexpr SDL_Keycode 键_b = SDLK_B;
inline constexpr SDL_Keycode 键_c = SDLK_C;
inline constexpr SDL_Keycode 键_d = SDLK_D;
inline constexpr SDL_Keycode 键_e = SDLK_E;
inline constexpr SDL_Keycode 键_f = SDLK_F;
inline constexpr SDL_Keycode 键_g = SDLK_G;
inline constexpr SDL_Keycode 键_h = SDLK_H;
inline constexpr SDL_Keycode 键_i = SDLK_I;
inline constexpr SDL_Keycode 键_j = SDLK_J;
inline constexpr SDL_Keycode 键_k = SDLK_K;
inline constexpr SDL_Keycode 键_l = SDLK_L;
inline constexpr SDL_Keycode 键_m = SDLK_M;
inline constexpr SDL_Keycode 键_n = SDLK_N;
inline constexpr SDL_Keycode 键_o = SDLK_O;
inline constexpr SDL_Keycode 键_p = SDLK_P;
inline constexpr SDL_Keycode 键_q = SDLK_Q;
inline constexpr SDL_Keycode 键_r = SDLK_R;
inline constexpr SDL_Keycode 键_s = SDLK_S;
inline constexpr SDL_Keycode 键_t = SDLK_T;
inline constexpr SDL_Keycode 键_u = SDLK_U;
inline constexpr SDL_Keycode 键_v = SDLK_V;
inline constexpr SDL_Keycode 键_w = SDLK_W;
inline constexpr SDL_Keycode 键_x = SDLK_X;
inline constexpr SDL_Keycode 键_y = SDLK_Y;
inline constexpr SDL_Keycode 键_z = SDLK_Z;

// ============================
//  中文别名 — 数字键
// ============================
inline constexpr SDL_Keycode 键_0 = SDLK_0;
inline constexpr SDL_Keycode 键_1 = SDLK_1;
inline constexpr SDL_Keycode 键_2 = SDLK_2;
inline constexpr SDL_Keycode 键_3 = SDLK_3;
inline constexpr SDL_Keycode 键_4 = SDLK_4;
inline constexpr SDL_Keycode 键_5 = SDLK_5;
inline constexpr SDL_Keycode 键_6 = SDLK_6;
inline constexpr SDL_Keycode 键_7 = SDLK_7;
inline constexpr SDL_Keycode 键_8 = SDLK_8;
inline constexpr SDL_Keycode 键_9 = SDLK_9;

// ============================
//  中文别名 — 功能键
// ============================
inline constexpr SDL_Keycode 键_f1  = SDLK_F1;
inline constexpr SDL_Keycode 键_f2  = SDLK_F2;
inline constexpr SDL_Keycode 键_f3  = SDLK_F3;
inline constexpr SDL_Keycode 键_f4  = SDLK_F4;
inline constexpr SDL_Keycode 键_f5  = SDLK_F5;
inline constexpr SDL_Keycode 键_f6  = SDLK_F6;
inline constexpr SDL_Keycode 键_f7  = SDLK_F7;
inline constexpr SDL_Keycode 键_f8  = SDLK_F8;
inline constexpr SDL_Keycode 键_f9  = SDLK_F9;
inline constexpr SDL_Keycode 键_f10 = SDLK_F10;
inline constexpr SDL_Keycode 键_f11 = SDLK_F11;
inline constexpr SDL_Keycode 键_f12 = SDLK_F12;

// ============================
//  中文别名 — 方向键
// ============================
inline constexpr SDL_Keycode 键_上 = SDLK_UP;
inline constexpr SDL_Keycode 键_下 = SDLK_DOWN;
inline constexpr SDL_Keycode 键_左 = SDLK_LEFT;
inline constexpr SDL_Keycode 键_右 = SDLK_RIGHT;

// ============================
//  中文别名 — 常用编辑/控制键
// ============================
inline constexpr SDL_Keycode 键_回车   = SDLK_RETURN;
inline constexpr SDL_Keycode 键_退出   = SDLK_ESCAPE;
inline constexpr SDL_Keycode 键_退格   = SDLK_BACKSPACE;
inline constexpr SDL_Keycode 键_制表   = SDLK_TAB;
inline constexpr SDL_Keycode 键_空格   = SDLK_SPACE;
inline constexpr SDL_Keycode 键_删除   = SDLK_DELETE;
inline constexpr SDL_Keycode 键_插入   = SDLK_INSERT;
inline constexpr SDL_Keycode 键_开头   = SDLK_HOME;
inline constexpr SDL_Keycode 键_末尾   = SDLK_END;
inline constexpr SDL_Keycode 键_上页   = SDLK_PAGEUP;
inline constexpr SDL_Keycode 键_下页   = SDLK_PAGEDOWN;

// ============================
//  中文别名 — 修饰键
// ============================
inline constexpr SDL_Keycode 键_左控制 = SDLK_LCTRL;
inline constexpr SDL_Keycode 键_左换挡 = SDLK_LSHIFT;
inline constexpr SDL_Keycode 键_左交替 = SDLK_LALT;
inline constexpr SDL_Keycode 键_左系统 = SDLK_LGUI;
inline constexpr SDL_Keycode 键_右控制 = SDLK_RCTRL;
inline constexpr SDL_Keycode 键_右换挡 = SDLK_RSHIFT;
inline constexpr SDL_Keycode 键_右交替 = SDLK_RALT;
inline constexpr SDL_Keycode 键_右系统 = SDLK_RGUI;

// ============================
//  中文别名 — 锁定键
// ============================
inline constexpr SDL_Keycode 键_大写锁定 = SDLK_CAPSLOCK;
inline constexpr SDL_Keycode 键_数字锁定 = SDLK_NUMLOCKCLEAR;
inline constexpr SDL_Keycode 键_滚动锁定 = SDLK_SCROLLLOCK;

// ============================
//  中文别名 — 其它键
// ============================
inline constexpr SDL_Keycode 键_打印屏幕 = SDLK_PRINTSCREEN;
inline constexpr SDL_Keycode 键_暂停     = SDLK_PAUSE;

// ============================
//  中文别名 — 符号键
// ============================
inline constexpr SDL_Keycode 键_减号   = SDLK_MINUS;
inline constexpr SDL_Keycode 键_等号   = SDLK_EQUALS;
inline constexpr SDL_Keycode 键_左括号 = SDLK_LEFTBRACKET;
inline constexpr SDL_Keycode 键_右括号 = SDLK_RIGHTBRACKET;
inline constexpr SDL_Keycode 键_反斜杠 = SDLK_BACKSLASH;
inline constexpr SDL_Keycode 键_分号   = SDLK_SEMICOLON;
inline constexpr SDL_Keycode 键_引号   = SDLK_APOSTROPHE;
inline constexpr SDL_Keycode 键_逗号   = SDLK_COMMA;
inline constexpr SDL_Keycode 键_句号   = SDLK_PERIOD;
inline constexpr SDL_Keycode 键_斜杠   = SDLK_SLASH;
inline constexpr SDL_Keycode 键_重音符 = SDLK_GRAVE;

// ============================
//  中文别名 — 小键盘
// ============================
inline constexpr SDL_Keycode 键_小键盘0  = SDLK_KP_0;
inline constexpr SDL_Keycode 键_小键盘1  = SDLK_KP_1;
inline constexpr SDL_Keycode 键_小键盘2  = SDLK_KP_2;
inline constexpr SDL_Keycode 键_小键盘3  = SDLK_KP_3;
inline constexpr SDL_Keycode 键_小键盘4  = SDLK_KP_4;
inline constexpr SDL_Keycode 键_小键盘5  = SDLK_KP_5;
inline constexpr SDL_Keycode 键_小键盘6  = SDLK_KP_6;
inline constexpr SDL_Keycode 键_小键盘7  = SDLK_KP_7;
inline constexpr SDL_Keycode 键_小键盘8  = SDLK_KP_8;
inline constexpr SDL_Keycode 键_小键盘9  = SDLK_KP_9;
inline constexpr SDL_Keycode 键_小键盘点 = SDLK_KP_PERIOD;
inline constexpr SDL_Keycode 键_小键盘除 = SDLK_KP_DIVIDE;
inline constexpr SDL_Keycode 键_小键盘乘 = SDLK_KP_MULTIPLY;
inline constexpr SDL_Keycode 键_小键盘减 = SDLK_KP_MINUS;
inline constexpr SDL_Keycode 键_小键盘加 = SDLK_KP_PLUS;
inline constexpr SDL_Keycode 键_小键盘回车 = SDLK_KP_ENTER;

} // namespace youklx
