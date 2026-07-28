namespace youklx{
    // ===== 鼠标按键 =====
    constexpr auto yk_lbutton = 1;    // VK_LBUTTON   鼠标左键
    constexpr auto yk_rbutton = 2;    // VK_RBUTTON   鼠标右键
    constexpr auto yk_cancel = 3;     // VK_CANCEL    Ctrl+Break 中断
    constexpr auto yk_mbutton = 4;    // VK_MBUTTON   鼠标中键
    constexpr auto yk_xbutton1 = 5;   // VK_XBUTTON1  鼠标侧键 1
    constexpr auto yk_xbutton2 = 6;   // VK_XBUTTON2  鼠标侧键 2

    // ===== 常用控制键 =====
    constexpr auto yk_backspace = 8;    // VK_BACK      退格键
    constexpr auto yk_tab = 9;          // VK_TAB       制表键
    constexpr auto yk_clear = 12;       // VK_CLEAR     清除键
    constexpr auto yk_enter = 13;       // VK_RETURN    回车键
    constexpr auto yk_shift = 16;       // VK_SHIFT     通用 Shift（与左右码会同时触发）
    constexpr auto yk_ctrl = 17;        // VK_CONTROL   通用 Ctrl（与左右码会同时触发）
    constexpr auto yk_alt = 18;         // VK_MENU      通用 Alt（与左右码会同时触发）
    constexpr auto yk_pause = 19;       // VK_PAUSE     暂停键
    constexpr auto yk_capslock = 20;    // VK_CAPITAL   大写锁定
    constexpr auto yk_escape = 27;      // VK_ESCAPE    Esc
    constexpr auto yk_space = 32;       // VK_SPACE     空格
    constexpr auto yk_pageup = 33;      // VK_PRIOR     上翻页 PageUp
    constexpr auto yk_pagedown = 34;    // VK_NEXT      下翻页 PageDown
    constexpr auto yk_end = 35;         // VK_END
    constexpr auto yk_home = 36;        // VK_HOME
    constexpr auto yk_left = 37;        // VK_LEFT      方向键 左
    constexpr auto yk_up = 38;          // VK_UP        方向键 上
    constexpr auto yk_right = 39;       // VK_RIGHT     方向键 右
    constexpr auto yk_down = 40;        // VK_DOWN      方向键 下
    constexpr auto yk_select = 41;      // VK_SELECT    选择键
    constexpr auto yk_print = 42;       // VK_PRINT     打印键
    constexpr auto yk_execute = 43;     // VK_EXECUTE   执行键
    constexpr auto yk_printscreen = 44; // VK_SNAPSHOT  截屏键 PrintScreen
    constexpr auto yk_insert = 45;      // VK_INSERT    插入键
    constexpr auto yk_delete = 46;      // VK_DELETE    删除键
    constexpr auto yk_help = 47;        // VK_HELP      帮助键

    // ===== IME 输入法相关 =====
    constexpr auto yk_kana = 21;        // VK_KANA       假名/韩文模式
    constexpr auto yk_ime_on = 22;      // VK_IME_ON     打开输入法
    constexpr auto yk_junja = 23;       // VK_JUNJA      韩文 Junja 模式
    constexpr auto yk_final = 24;       // VK_FINAL      输入法最终模式
    constexpr auto yk_hanja = 25;       // VK_HANJA      韩文汉字/日文汉字模式
    constexpr auto yk_ime_off = 26;     // VK_IME_OFF    关闭输入法
    constexpr auto yk_convert = 28;     // VK_CONVERT    输入法转换
    constexpr auto yk_nonconvert = 29;  // VK_NONCONVERT 输入法不转换
    constexpr auto yk_accept = 30;      // VK_ACCEPT     输入法接受
    constexpr auto yk_modechange = 31;  // VK_MODECHANGE 输入法模式切换

    // ===== 主键盘数字 0-9 =====
    constexpr auto yk_0 = 48;
    constexpr auto yk_1 = 49;
    constexpr auto yk_2 = 50;
    constexpr auto yk_3 = 51;
    constexpr auto yk_4 = 52;
    constexpr auto yk_5 = 53;
    constexpr auto yk_6 = 54;
    constexpr auto yk_7 = 55;
    constexpr auto yk_8 = 56;
    constexpr auto yk_9 = 57;

    // ===== 字母键 A-Z =====
    constexpr auto yk_a = 65;
    constexpr auto yk_b = 66;
    constexpr auto yk_c = 67;
    constexpr auto yk_d = 68;
    constexpr auto yk_e = 69;
    constexpr auto yk_f = 70;
    constexpr auto yk_g = 71;
    constexpr auto yk_h = 72;
    constexpr auto yk_i = 73;
    constexpr auto yk_j = 74;
    constexpr auto yk_k = 75;
    constexpr auto yk_l = 76;
    constexpr auto yk_m = 77;
    constexpr auto yk_n = 78;
    constexpr auto yk_o = 79;
    constexpr auto yk_p = 80;
    constexpr auto yk_q = 81;
    constexpr auto yk_r = 82;
    constexpr auto yk_s = 83;
    constexpr auto yk_t = 84;
    constexpr auto yk_u = 85;
    constexpr auto yk_v = 86;
    constexpr auto yk_w = 87;
    constexpr auto yk_x = 88;
    constexpr auto yk_y = 89;
    constexpr auto yk_z = 90;

    // ===== Windows / 系统键 =====
    constexpr auto yk_lwin = 91;   // VK_LWIN  左 Win 键
    constexpr auto yk_rwin = 92;   // VK_RWIN  右 Win 键
    constexpr auto yk_apps = 93;   // VK_APPS  菜单键
    constexpr auto yk_sleep = 95;  // VK_SLEEP 睡眠键

    // ===== 小键盘 =====
    constexpr auto yk_num0 = 96;
    constexpr auto yk_num1 = 97;
    constexpr auto yk_num2 = 98;
    constexpr auto yk_num3 = 99;
    constexpr auto yk_num4 = 100;
    constexpr auto yk_num5 = 101;
    constexpr auto yk_num6 = 102;
    constexpr auto yk_num7 = 103;
    constexpr auto yk_num8 = 104;
    constexpr auto yk_num9 = 105;
    constexpr auto yk_multiply = 106;   // VK_MULTIPLY  小键盘 *
    constexpr auto yk_add = 107;        // VK_ADD       小键盘 +
    constexpr auto yk_separator = 108;  // VK_SEPARATOR 小键盘分隔符
    constexpr auto yk_subtract = 109;   // VK_SUBTRACT  小键盘 -
    constexpr auto yk_decimal = 110;    // VK_DECIMAL   小键盘 .
    constexpr auto yk_divide = 111;     // VK_DIVIDE    小键盘 /

    // ===== 功能键 F1-F24 =====
    constexpr auto yk_f1 = 112;
    constexpr auto yk_f2 = 113;
    constexpr auto yk_f3 = 114;
    constexpr auto yk_f4 = 115;
    constexpr auto yk_f5 = 116;
    constexpr auto yk_f6 = 117;
    constexpr auto yk_f7 = 118;
    constexpr auto yk_f8 = 119;
    constexpr auto yk_f9 = 120;
    constexpr auto yk_f10 = 121;
    constexpr auto yk_f11 = 122;
    constexpr auto yk_f12 = 123;
    constexpr auto yk_f13 = 124;
    constexpr auto yk_f14 = 125;
    constexpr auto yk_f15 = 126;
    constexpr auto yk_f16 = 127;
    constexpr auto yk_f17 = 128;
    constexpr auto yk_f18 = 129;
    constexpr auto yk_f19 = 130;
    constexpr auto yk_f20 = 131;
    constexpr auto yk_f21 = 132;
    constexpr auto yk_f22 = 133;
    constexpr auto yk_f23 = 134;
    constexpr auto yk_f24 = 135;

    // ===== 锁定键 =====
    constexpr auto yk_numlock = 144;    // VK_NUMLOCK 数字锁定
    constexpr auto yk_scrolllock = 145; // VK_SCROLL  滚动锁定

    // ===== 左右修饰键（与上方通用码会同时触发） =====
    constexpr auto yk_lshift = 160;  // VK_LSHIFT    左 Shift
    constexpr auto yk_rshift = 161;  // VK_RSHIFT    右 Shift
    constexpr auto yk_lctrl = 162;   // VK_LCONTROL  左 Ctrl
    constexpr auto yk_rctrl = 163;   // VK_RCONTROL  右 Ctrl
    constexpr auto yk_lalt = 164;    // VK_LMENU     左 Alt
    constexpr auto yk_ralt = 165;    // VK_RMENU     右 Alt

    // ===== 浏览器控制键 =====
    constexpr auto yk_browser_back = 166;      // VK_BROWSER_BACK      后退
    constexpr auto yk_browser_forward = 167;   // VK_BROWSER_FORWARD   前进
    constexpr auto yk_browser_refresh = 168;   // VK_BROWSER_REFRESH   刷新
    constexpr auto yk_browser_stop = 169;      // VK_BROWSER_STOP      停止
    constexpr auto yk_browser_search = 170;    // VK_BROWSER_SEARCH    搜索
    constexpr auto yk_browser_favorites = 171; // VK_BROWSER_FAVORITES 收藏夹
    constexpr auto yk_browser_home = 172;      // VK_BROWSER_HOME      主页

    // ===== 音量 / 媒体键 =====
    constexpr auto yk_volume_mute = 173;       // VK_VOLUME_MUTE         静音
    constexpr auto yk_volume_down = 174;       // VK_VOLUME_DOWN         音量减
    constexpr auto yk_volume_up = 175;         // VK_VOLUME_UP           音量加
    constexpr auto yk_media_next = 176;        // VK_MEDIA_NEXT_TRACK    下一曲
    constexpr auto yk_media_prev = 177;        // VK_MEDIA_PREV_TRACK    上一曲
    constexpr auto yk_media_stop = 178;        // VK_MEDIA_STOP          停止播放
    constexpr auto yk_media_play_pause = 179;  // VK_MEDIA_PLAY_PAUSE    播放/暂停
    constexpr auto yk_launch_mail = 180;       // VK_LAUNCH_MAIL         打开邮件
    constexpr auto yk_launch_media = 181;      // VK_LAUNCH_MEDIA_SELECT 打开媒体播放器
    constexpr auto yk_launch_app1 = 182;       // VK_LAUNCH_APP1         自定义应用 1
    constexpr auto yk_launch_app2 = 183;       // VK_LAUNCH_APP2         自定义应用 2

    // ===== OEM 标点键（注释以美式键盘布局标注，其他布局含义不同） =====
    constexpr auto yk_oem_1 = 186;      // VK_OEM_1      ; :
    constexpr auto yk_oem_plus = 187;   // VK_OEM_PLUS   = +
    constexpr auto yk_oem_comma = 188;  // VK_OEM_COMMA  , <
    constexpr auto yk_oem_minus = 189;  // VK_OEM_MINUS  - _
    constexpr auto yk_oem_period = 190; // VK_OEM_PERIOD . >
    constexpr auto yk_oem_2 = 191;      // VK_OEM_2      / ?
    constexpr auto yk_oem_3 = 192;      // VK_OEM_3      ` ~
    constexpr auto yk_oem_4 = 219;      // VK_OEM_4      [ {
    constexpr auto yk_oem_5 = 220;      // VK_OEM_5      \ |
    constexpr auto yk_oem_6 = 221;      // VK_OEM_6      ] }
    constexpr auto yk_oem_7 = 222;      // VK_OEM_7      ' "
    constexpr auto yk_oem_8 = 223;      // VK_OEM_8      OEM 保留
    constexpr auto yk_oem_102 = 226;    // VK_OEM_102    102 键键盘的 < > 键

    // ===== 其他特殊键 =====
    constexpr auto yk_processkey = 229; // VK_PROCESSKEY IME 处理键
    constexpr auto yk_packet = 231;     // VK_PACKET     用于传递 Unicode 字符
    constexpr auto yk_attn = 246;       // VK_ATTN
    constexpr auto yk_crsel = 247;      // VK_CRSEL      光标选择
    constexpr auto yk_exsel = 248;      // VK_EXSEL      扩展选择
    constexpr auto yk_eraseeof = 249;   // VK_EREOF      擦除到行尾
    constexpr auto yk_play = 250;       // VK_PLAY       播放
    constexpr auto yk_zoom = 251;       // VK_ZOOM       缩放
    constexpr auto yk_noname = 252;     // VK_NONAME     保留
    constexpr auto yk_pa1 = 253;        // VK_PA1
    constexpr auto yk_oem_clear = 254;  // VK_OEM_CLEAR  清除
}
