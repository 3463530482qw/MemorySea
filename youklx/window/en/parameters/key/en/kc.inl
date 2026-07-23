namespace youklx {
    typedef Uint32 yk_Keycode;
    #define yk_extended_mask          (1u << 29)
    #define yk_scancode_mask          (1u << 30)
    #define yk_scancode_to_keycode(X)  (X | yk_scancode_mask)
    #define yk_unknown                0x00000000u /**< 0 */
    #define yk_return                 0x0000000du /**< '\r' */
    #define yk_escape                 0x0000001bu /**< '\x1B' */
    #define yk_backspace              0x00000008u /**< '\b' */
    #define yk_tab                    0x00000009u /**< '\t' */
    #define yk_space                  0x00000020u /**< ' ' */
    #define yk_exclaim                0x00000021u /**< '!' */
    #define yk_dblapostrophe          0x00000022u /**< '"' */
    #define yk_hash                   0x00000023u /**< '#' */
    #define yk_dollar                 0x00000024u /**< '$' */
    #define yk_percent                0x00000025u /**< '%' */
    #define yk_ampersand              0x00000026u /**< '&' */
    #define yk_apostrophe             0x00000027u /**< '\'' */
    #define yk_leftparen              0x00000028u /**< '(' */
    #define yk_rightparen             0x00000029u /**< ')' */
    #define yk_asterisk               0x0000002au /**< '*' */
    #define yk_plus                   0x0000002bu /**< '+' */
    #define yk_comma                  0x0000002cu /**< ',' */
    #define yk_minus                  0x0000002du /**< '-' */
    #define yk_period                 0x0000002eu /**< '.' */
    #define yk_slash                  0x0000002fu /**< '/' */
    #define yk_0                      0x00000030u /**< '0' */
    #define yk_1                      0x00000031u /**< '1' */
    #define yk_2                      0x00000032u /**< '2' */
    #define yk_3                      0x00000033u /**< '3' */
    #define yk_4                      0x00000034u /**< '4' */
    #define yk_5                      0x00000035u /**< '5' */
    #define yk_6                      0x00000036u /**< '6' */
    #define yk_7                      0x00000037u /**< '7' */
    #define yk_8                      0x00000038u /**< '8' */
    #define yk_9                      0x00000039u /**< '9' */
    #define yk_colon                  0x0000003au /**< ':' */
    #define yk_semicolon              0x0000003bu /**< ';' */
    #define yk_less                   0x0000003cu /**< '<' */
    #define yk_equals                 0x0000003du /**< '=' */
    #define yk_greater                0x0000003eu /**< '>' */
    #define yk_question               0x0000003fu /**< '?' */
    #define yk_at                     0x00000040u /**< '@' */
    #define yk_leftbracket            0x0000005bu /**< '[' */
    #define yk_backslash              0x0000005cu /**< '\\' */
    #define yk_rightbracket           0x0000005du /**< ']' */
    #define yk_caret                  0x0000005eu /**< '^' */
    #define yk_underscore             0x0000005fu /**< '_' */
    #define yk_grave                  0x00000060u /**< '`' */
    #define yk_a                      0x00000061u /**< 'a' */
    #define yk_b                      0x00000062u /**< 'b' */
    #define yk_c                      0x00000063u /**< 'c' */
    #define yk_d                      0x00000064u /**< 'd' */
    #define yk_e                      0x00000065u /**< 'e' */
    #define yk_f                      0x00000066u /**< 'f' */
    #define yk_g                      0x00000067u /**< 'g' */
    #define yk_h                      0x00000068u /**< 'h' */
    #define yk_i                      0x00000069u /**< 'i' */
    #define yk_j                      0x0000006au /**< 'j' */
    #define yk_k                      0x0000006bu /**< 'k' */
    #define yk_l                      0x0000006cu /**< 'l' */
    #define yk_m                      0x0000006du /**< 'm' */
    #define yk_n                      0x0000006eu /**< 'n' */
    #define yk_o                      0x0000006fu /**< 'o' */
    #define yk_p                      0x00000070u /**< 'p' */
    #define yk_q                      0x00000071u /**< 'q' */
    #define yk_r                      0x00000072u /**< 'r' */
    #define yk_s                      0x00000073u /**< 's' */
    #define yk_t                      0x00000074u /**< 't' */
    #define yk_u                      0x00000075u /**< 'u' */
    #define yk_v                      0x00000076u /**< 'v' */
    #define yk_w                      0x00000077u /**< 'w' */
    #define yk_x                      0x00000078u /**< 'x' */
    #define yk_y                      0x00000079u /**< 'y' */
    #define yk_z                      0x0000007au /**< 'z' */
    #define yk_leftbrace              0x0000007bu /**< '{' */
    #define yk_pipe                   0x0000007cu /**< '|' */
    #define yk_rightbrace             0x0000007du /**< '}' */
    #define yk_tilde                  0x0000007eu /**< '~' */
    #define yk_delete                 0x0000007fu /**< '\x7F' */
    #define yk_plusminus              0x000000b1u /**< '\xB1' */
    #define yk_capslock               0x40000039u /**< yk_scancode_to_keycode(SDL_scancode_CAPSLOCK) */
    #define yk_f1                     0x4000003au /**< yk_scancode_to_keycode(SDL_scancode_F1) */
    #define yk_f2                     0x4000003bu /**< yk_scancode_to_keycode(SDL_scancode_F2) */
    #define yk_f3                     0x4000003cu /**< yk_scancode_to_keycode(SDL_scancode_F3) */
    #define yk_f4                     0x4000003du /**< yk_scancode_to_keycode(SDL_scancode_F4) */
    #define yk_f5                     0x4000003eu /**< yk_scancode_to_keycode(SDL_scancode_F5) */
    #define yk_f6                     0x4000003fu /**< yk_scancode_to_keycode(SDL_scancode_F6) */
    #define yk_f7                     0x40000040u /**< yk_scancode_to_keycode(SDL_scancode_F7) */
    #define yk_f8                     0x40000041u /**< yk_scancode_to_keycode(SDL_scancode_F8) */
    #define yk_f9                     0x40000042u /**< yk_scancode_to_keycode(SDL_scancode_F9) */
    #define yk_f10                    0x40000043u /**< yk_scancode_to_keycode(SDL_scancode_F10) */
    #define yk_f11                    0x40000044u /**< yk_scancode_to_keycode(SDL_scancode_F11) */
    #define yk_f12                    0x40000045u /**< yk_scancode_to_keycode(SDL_scancode_F12) */
    #define yk_printscreen            0x40000046u /**< yk_scancode_to_keycode(SDL_scancode_PRINTSCREEN) */
    #define yk_scrolllock             0x40000047u /**< yk_scancode_to_keycode(SDL_scancode_SCROLLLOCK) */
    #define yk_pause                  0x40000048u /**< yk_scancode_to_keycode(SDL_scancode_PAUSE) */
    #define yk_insert                 0x40000049u /**< yk_scancode_to_keycode(SDL_scancode_INSERT) */
    #define yk_home                   0x4000004au /**< yk_scancode_to_keycode(SDL_scancode_HOME) */
    #define yk_pageup                 0x4000004bu /**< yk_scancode_to_keycode(SDL_scancode_PAGEUP) */
    #define yk_end                    0x4000004du /**< yk_scancode_to_keycode(SDL_scancode_END) */
    #define yk_pagedown               0x4000004eu /**< yk_scancode_to_keycode(SDL_scancode_PAGEDOWN) */
    #define yk_right                  0x4000004fu /**< yk_scancode_to_keycode(SDL_scancode_RIGHT) */
    #define yk_left                   0x40000050u /**< yk_scancode_to_keycode(SDL_scancode_LEFT) */
    #define yk_down                   0x40000051u /**< yk_scancode_to_keycode(SDL_scancode_DOWN) */
    #define yk_up                     0x40000052u /**< yk_scancode_to_keycode(SDL_scancode_UP) */
    #define yk_numlockclear           0x40000053u /**< yk_scancode_to_keycode(SDL_scancode_NUMLOCKCLEAR) */
    #define yk_kp_divide              0x40000054u /**< yk_scancode_to_keycode(SDL_scancode_KP_DIVIDE) */
    #define yk_kp_multiply            0x40000055u /**< yk_scancode_to_keycode(SDL_scancode_KP_MULTIPLY) */
    #define yk_kp_minus               0x40000056u /**< yk_scancode_to_keycode(SDL_scancode_KP_MINUS) */
    #define yk_kp_plus                0x40000057u /**< yk_scancode_to_keycode(SDL_scancode_KP_PLUS) */
    #define yk_kp_enter               0x40000058u /**< yk_scancode_to_keycode(SDL_scancode_KP_ENTER) */
    #define yk_kp_1                   0x40000059u /**< yk_scancode_to_keycode(SDL_scancode_KP_1) */
    #define yk_kp_2                   0x4000005au /**< yk_scancode_to_keycode(SDL_scancode_KP_2) */
    #define yk_kp_3                   0x4000005bu /**< yk_scancode_to_keycode(SDL_scancode_KP_3) */
    #define yk_kp_4                   0x4000005cu /**< yk_scancode_to_keycode(SDL_scancode_KP_4) */
    #define yk_kp_5                   0x4000005du /**< yk_scancode_to_keycode(SDL_scancode_KP_5) */
    #define yk_kp_6                   0x4000005eu /**< yk_scancode_to_keycode(SDL_scancode_KP_6) */
    #define yk_kp_7                   0x4000005fu /**< yk_scancode_to_keycode(SDL_scancode_KP_7) */
    #define yk_kp_8                   0x40000060u /**< yk_scancode_to_keycode(SDL_scancode_KP_8) */
    #define yk_kp_9                   0x40000061u /**< yk_scancode_to_keycode(SDL_scancode_KP_9) */
    #define yk_kp_0                   0x40000062u /**< yk_scancode_to_keycode(SDL_scancode_KP_0) */
    #define yk_kp_period              0x40000063u /**< yk_scancode_to_keycode(SDL_scancode_KP_PERIOD) */
    #define yk_application            0x40000065u /**< yk_scancode_to_keycode(SDL_scancode_APPLICATION) */
    #define yk_power                  0x40000066u /**< yk_scancode_to_keycode(SDL_scancode_POWER) */
    #define yk_kp_equals              0x40000067u /**< yk_scancode_to_keycode(SDL_scancode_KP_EQUALS) */
    #define yk_f13                    0x40000068u /**< yk_scancode_to_keycode(SDL_scancode_F13) */
    #define yk_f14                    0x40000069u /**< yk_scancode_to_keycode(SDL_scancode_F14) */
    #define yk_f15                    0x4000006au /**< yk_scancode_to_keycode(SDL_scancode_F15) */
    #define yk_f16                    0x4000006bu /**< yk_scancode_to_keycode(SDL_scancode_F16) */
    #define yk_f17                    0x4000006cu /**< yk_scancode_to_keycode(SDL_scancode_F17) */
    #define yk_f18                    0x4000006du /**< yk_scancode_to_keycode(SDL_scancode_F18) */
    #define yk_f19                    0x4000006eu /**< yk_scancode_to_keycode(SDL_scancode_F19) */
    #define yk_f20                    0x4000006fu /**< yk_scancode_to_keycode(SDL_scancode_F20) */
    #define yk_f21                    0x40000070u /**< yk_scancode_to_keycode(SDL_scancode_F21) */
    #define yk_f22                    0x40000071u /**< yk_scancode_to_keycode(SDL_scancode_F22) */
    #define yk_f23                    0x40000072u /**< yk_scancode_to_keycode(SDL_scancode_F23) */
    #define yk_f24                    0x40000073u /**< yk_scancode_to_keycode(SDL_scancode_F24) */
    #define yk_execute                0x40000074u /**< yk_scancode_to_keycode(SDL_scancode_EXECUTE) */
    #define yk_help                   0x40000075u /**< yk_scancode_to_keycode(SDL_scancode_HELP) */
    #define yk_menu                   0x40000076u /**< yk_scancode_to_keycode(SDL_scancode_MENU) */
    #define yk_select                 0x40000077u /**< yk_scancode_to_keycode(SDL_scancode_SELECT) */
    #define yk_stop                   0x40000078u /**< yk_scancode_to_keycode(SDL_scancode_STOP) */
    #define yk_again                  0x40000079u /**< yk_scancode_to_keycode(SDL_scancode_AGAIN) */
    #define yk_undo                   0x4000007au /**< yk_scancode_to_keycode(SDL_scancode_UNDO) */
    #define yk_cut                    0x4000007bu /**< yk_scancode_to_keycode(SDL_scancode_CUT) */
    #define yk_copy                   0x4000007cu /**< yk_scancode_to_keycode(SDL_scancode_COPY) */
    #define yk_paste                  0x4000007du /**< yk_scancode_to_keycode(SDL_scancode_PASTE) */
    #define yk_find                   0x4000007eu /**< yk_scancode_to_keycode(SDL_scancode_FIND) */
    #define yk_mute                   0x4000007fu /**< yk_scancode_to_keycode(SDL_scancode_MUTE) */
    #define yk_volumeup               0x40000080u /**< yk_scancode_to_keycode(SDL_scancode_VOLUMEUP) */
    #define yk_volumedown             0x40000081u /**< yk_scancode_to_keycode(SDL_scancode_VOLUMEDOWN) */
    #define yk_kp_comma               0x40000085u /**< yk_scancode_to_keycode(SDL_scancode_KP_COMMA) */
    #define yk_kp_equalsas400         0x40000086u /**< yk_scancode_to_keycode(SDL_scancode_KP_EQUALSAS400) */
    #define yk_alterase               0x40000099u /**< yk_scancode_to_keycode(SDL_scancode_ALTERASE) */
    #define yk_sysreq                 0x4000009au /**< yk_scancode_to_keycode(SDL_scancode_SYSREQ) */
    #define yk_cancel                 0x4000009bu /**< yk_scancode_to_keycode(SDL_scancode_CANCEL) */
    #define yk_clear                  0x4000009cu /**< yk_scancode_to_keycode(SDL_scancode_CLEAR) */
    #define yk_prior                  0x4000009du /**< yk_scancode_to_keycode(SDL_scancode_PRIOR) */
    #define yk_return2                0x4000009eu /**< yk_scancode_to_keycode(SDL_scancode_RETURN2) */
    #define yk_separator              0x4000009fu /**< yk_scancode_to_keycode(SDL_scancode_SEPARATOR) */
    #define yk_out                    0x400000a0u /**< yk_scancode_to_keycode(SDL_scancode_OUT) */
    #define yk_oper                   0x400000a1u /**< yk_scancode_to_keycode(SDL_scancode_OPER) */
    #define yk_clearagain             0x400000a2u /**< yk_scancode_to_keycode(SDL_scancode_CLEARAGAIN) */
    #define yk_crsel                  0x400000a3u /**< yk_scancode_to_keycode(SDL_scancode_CRSEL) */
    #define yk_exsel                  0x400000a4u /**< yk_scancode_to_keycode(SDL_scancode_EXSEL) */
    #define yk_kp_00                  0x400000b0u /**< yk_scancode_to_keycode(SDL_scancode_KP_00) */
    #define yk_kp_000                 0x400000b1u /**< yk_scancode_to_keycode(SDL_scancode_KP_000) */
    #define yk_thousandsseparator     0x400000b2u /**< yk_scancode_to_keycode(SDL_scancode_THOUSANDSSEPARATOR) */
    #define yk_decimalseparator       0x400000b3u /**< yk_scancode_to_keycode(SDL_scancode_DECIMALSEPARATOR) */
    #define yk_currencyunit           0x400000b4u /**< yk_scancode_to_keycode(SDL_scancode_CURRENCYUNIT) */
    #define yk_currencysubunit        0x400000b5u /**< yk_scancode_to_keycode(SDL_scancode_CURRENCYSUBUNIT) */
    #define yk_kp_leftparen           0x400000b6u /**< yk_scancode_to_keycode(SDL_scancode_KP_LEFTPAREN) */
    #define yk_kp_rightparen          0x400000b7u /**< yk_scancode_to_keycode(SDL_scancode_KP_RIGHTPAREN) */
    #define yk_kp_leftbrace           0x400000b8u /**< yk_scancode_to_keycode(SDL_scancode_KP_LEFTBRACE) */
    #define yk_kp_rightbrace          0x400000b9u /**< yk_scancode_to_keycode(SDL_scancode_KP_RIGHTBRACE) */
    #define yk_kp_tab                 0x400000bau /**< yk_scancode_to_keycode(SDL_scancode_KP_TAB) */
    #define yk_kp_backspace           0x400000bbu /**< yk_scancode_to_keycode(SDL_scancode_KP_BACKSPACE) */
    #define yk_kp_a                   0x400000bcu /**< yk_scancode_to_keycode(SDL_scancode_KP_A) */
    #define yk_kp_b                   0x400000bdu /**< yk_scancode_to_keycode(SDL_scancode_KP_B) */
    #define yk_kp_c                   0x400000beu /**< yk_scancode_to_keycode(SDL_scancode_KP_C) */
    #define yk_kp_d                   0x400000bfu /**< yk_scancode_to_keycode(SDL_scancode_KP_D) */
    #define yk_kp_e                   0x400000c0u /**< yk_scancode_to_keycode(SDL_scancode_KP_E) */
    #define yk_kp_f                   0x400000c1u /**< yk_scancode_to_keycode(SDL_scancode_KP_F) */
    #define yk_kp_xor                 0x400000c2u /**< yk_scancode_to_keycode(SDL_scancode_KP_XOR) */
    #define yk_kp_power               0x400000c3u /**< yk_scancode_to_keycode(SDL_scancode_KP_POWER) */
    #define yk_kp_percent             0x400000c4u /**< yk_scancode_to_keycode(SDL_scancode_KP_PERCENT) */
    #define yk_kp_less                0x400000c5u /**< yk_scancode_to_keycode(SDL_scancode_KP_LESS) */
    #define yk_kp_greater             0x400000c6u /**< yk_scancode_to_keycode(SDL_scancode_KP_GREATER) */
    #define yk_kp_ampersand           0x400000c7u /**< yk_scancode_to_keycode(SDL_scancode_KP_AMPERSAND) */
    #define yk_kp_dblampersand        0x400000c8u /**< yk_scancode_to_keycode(SDL_scancode_KP_DBLAMPERSAND) */
    #define yk_kp_verticalbar         0x400000c9u /**< yk_scancode_to_keycode(SDL_scancode_KP_VERTICALBAR) */
    #define yk_kp_dblverticalbar      0x400000cau /**< yk_scancode_to_keycode(SDL_scancode_KP_DBLVERTICALBAR) */
    #define yk_kp_colon               0x400000cbu /**< yk_scancode_to_keycode(SDL_scancode_KP_COLON) */
    #define yk_kp_hash                0x400000ccu /**< yk_scancode_to_keycode(SDL_scancode_KP_HASH) */
    #define yk_kp_space               0x400000cdu /**< yk_scancode_to_keycode(SDL_scancode_KP_SPACE) */
    #define yk_kp_at                  0x400000ceu /**< yk_scancode_to_keycode(SDL_scancode_KP_AT) */
    #define yk_kp_exclam              0x400000cfu /**< yk_scancode_to_keycode(SDL_scancode_KP_EXCLAM) */
    #define yk_kp_memstore            0x400000d0u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMSTORE) */
    #define yk_kp_memrecall           0x400000d1u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMRECALL) */
    #define yk_kp_memclear            0x400000d2u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMCLEAR) */
    #define yk_kp_memadd              0x400000d3u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMADD) */
    #define yk_kp_memsubtract         0x400000d4u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMSUBTRACT) */
    #define yk_kp_memmultiply         0x400000d5u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMMULTIPLY) */
    #define yk_kp_memdivide           0x400000d6u /**< yk_scancode_to_keycode(SDL_scancode_KP_MEMDIVIDE) */
    #define yk_kp_plusminus           0x400000d7u /**< yk_scancode_to_keycode(SDL_scancode_KP_PLUSMINUS) */
    #define yk_kp_clear               0x400000d8u /**< yk_scancode_to_keycode(SDL_scancode_KP_CLEAR) */
    #define yk_kp_clearentry          0x400000d9u /**< yk_scancode_to_keycode(SDL_scancode_KP_CLEARENTRY) */
    #define yk_kp_binary              0x400000dau /**< yk_scancode_to_keycode(SDL_scancode_KP_BINARY) */
    #define yk_kp_octal               0x400000dbu /**< yk_scancode_to_keycode(SDL_scancode_KP_OCTAL) */
    #define yk_kp_decimal             0x400000dcu /**< yk_scancode_to_keycode(SDL_scancode_KP_DECIMAL) */
    #define yk_kp_hexadecimal         0x400000ddu /**< yk_scancode_to_keycode(SDL_scancode_KP_HEXADECIMAL) */
    #define yk_lctrl                  0x400000e0u /**< yk_scancode_to_keycode(SDL_scancode_LCTRL) */
    #define yk_lshift                 0x400000e1u /**< yk_scancode_to_keycode(SDL_scancode_LSHIFT) */
    #define yk_lalt                   0x400000e2u /**< yk_scancode_to_keycode(SDL_scancode_LALT) */
    #define yk_lgui                   0x400000e3u /**< yk_scancode_to_keycode(SDL_scancode_LGUI) */
    #define yk_rctrl                  0x400000e4u /**< yk_scancode_to_keycode(SDL_scancode_RCTRL) */
    #define yk_rshift                 0x400000e5u /**< yk_scancode_to_keycode(SDL_scancode_RSHIFT) */
    #define yk_ralt                   0x400000e6u /**< yk_scancode_to_keycode(SDL_scancode_RALT) */
    #define yk_rgui                   0x400000e7u /**< yk_scancode_to_keycode(SDL_scancode_RGUI) */
    #define yk_mode                   0x40000101u /**< yk_scancode_to_keycode(SDL_scancode_MODE) */
    #define yk_sleep                  0x40000102u /**< yk_scancode_to_keycode(SDL_scancode_SLEEP) */
    #define yk_wake                   0x40000103u /**< yk_scancode_to_keycode(SDL_scancode_WAKE) */
    #define yk_channel_increment      0x40000104u /**< yk_scancode_to_keycode(SDL_scancode_CHANNEL_INCREMENT) */
    #define yk_channel_decrement      0x40000105u /**< yk_scancode_to_keycode(SDL_scancode_CHANNEL_DECREMENT) */
    #define yk_media_play             0x40000106u /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_PLAY) */
    #define yk_media_pause            0x40000107u /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_PAUSE) */
    #define yk_media_record           0x40000108u /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_RECORD) */
    #define yk_media_fast_forward     0x40000109u /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_FAST_FORWARD) */
    #define yk_media_rewind           0x4000010au /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_REWIND) */
    #define yk_media_next_track       0x4000010bu /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_NEXT_TRACK) */
    #define yk_media_previous_track   0x4000010cu /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_PREVIOUS_TRACK) */
    #define yk_media_stop             0x4000010du /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_STOP) */
    #define yk_media_eject            0x4000010eu /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_EJECT) */
    #define yk_media_play_pause       0x4000010fu /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_PLAY_PAUSE) */
    #define yk_media_select           0x40000110u /**< yk_scancode_to_keycode(SDL_scancode_MEDIA_SELECT) */
    #define yk_ac_new                 0x40000111u /**< yk_scancode_to_keycode(SDL_scancode_AC_NEW) */
    #define yk_ac_open                0x40000112u /**< yk_scancode_to_keycode(SDL_scancode_AC_OPEN) */
    #define yk_ac_close               0x40000113u /**< yk_scancode_to_keycode(SDL_scancode_AC_CLOSE) */
    #define yk_ac_exit                0x40000114u /**< yk_scancode_to_keycode(SDL_scancode_AC_EXIT) */
    #define yk_ac_save                0x40000115u /**< yk_scancode_to_keycode(SDL_scancode_AC_SAVE) */
    #define yk_ac_print               0x40000116u /**< yk_scancode_to_keycode(SDL_scancode_AC_PRINT) */
    #define yk_ac_properties          0x40000117u /**< yk_scancode_to_keycode(SDL_scancode_AC_PROPERTIES) */
    #define yk_ac_search              0x40000118u /**< yk_scancode_to_keycode(SDL_scancode_AC_SEARCH) */
    #define yk_ac_home                0x40000119u /**< yk_scancode_to_keycode(SDL_scancode_AC_HOME) */
    #define yk_ac_back                0x4000011au /**< yk_scancode_to_keycode(SDL_scancode_AC_BACK) */
    #define yk_ac_forward             0x4000011bu /**< yk_scancode_to_keycode(SDL_scancode_AC_FORWARD) */
    #define yk_ac_stop                0x4000011cu /**< yk_scancode_to_keycode(SDL_scancode_AC_STOP) */
    #define yk_ac_refresh             0x4000011du /**< yk_scancode_to_keycode(SDL_scancode_AC_REFRESH) */
    #define yk_ac_bookmarks           0x4000011eu /**< yk_scancode_to_keycode(SDL_scancode_AC_BOOKMARKS) */
    #define yk_softleft               0x4000011fu /**< yk_scancode_to_keycode(SDL_scancode_SOFTLEFT) */
    #define yk_softright              0x40000120u /**< yk_scancode_to_keycode(SDL_scancode_SOFTRIGHT) */
    #define yk_call                   0x40000121u /**< yk_scancode_to_keycode(SDL_scancode_CALL) */
    #define yk_endcall                0x40000122u /**< yk_scancode_to_keycode(SDL_scancode_ENDCALL) */
    #define yk_left_tab               0x20000001u /**< Extended key Left Tab */
    #define yk_level5_shift           0x20000002u /**< Extended key Level 5 Shift */
    #define yk_multi_key_compose      0x20000003u /**< Extended key Multi-key Compose */
    #define yk_lmeta                  0x20000004u /**< Extended key Left Meta */
    #define yk_rmeta                  0x20000005u /**< Extended key Right Meta */
    #define yk_lhyper                 0x20000006u /**< Extended key Left Hyper */
    #define yk_rhyper                 0x20000007u /**< Extended key Right Hyper */
    typedef Uint16 yk_Keymod;

    #define yk_kmod_none   0x0000u /**< no modifier is applicable. */
    #define yk_kmod_lshift 0x0001u /**< the left Shift key is down. */
    #define yk_kmod_rshift 0x0002u /**< the right Shift key is down. */
    #define yk_kmod_level5 0x0004u /**< the Level 5 Shift key is down. */
    #define yk_kmod_lctrl  0x0040u /**< the left Ctrl (Control) key is down. */
    #define yk_kmod_rctrl  0x0080u /**< the right Ctrl (Control) key is down. */
    #define yk_kmod_lalt   0x0100u /**< the left Alt key is down. */
    #define yk_kmod_ralt   0x0200u /**< the right Alt key is down. */
    #define yk_kmod_lgui   0x0400u /**< the left GUI key (often the Windows key) is down. */
    #define yk_kmod_rgui   0x0800u /**< the right GUI key (often the Windows key) is down. */
    #define yk_kmod_num    0x1000u /**< the Num Lock key (may be located on an extended keypad) is down. */
    #define yk_kmod_caps   0x2000u /**< the Caps Lock key is down. */
    #define yk_kmod_mode   0x4000u /**< the !AltGr key is down. */
    #define yk_kmod_scroll 0x8000u /**< the Scroll Lock key is down. */
    #define yk_kmod_ctrl   (yk_kmod_lctrl | yk_kmod_rctrl)     /**< Any Ctrl key is down. */
    #define yk_kmod_shift  (yk_kmod_lshift | yk_kmod_rshift)   /**< Any Shift key is down. */
    #define yk_kmod_alt    (yk_kmod_lalt | yk_kmod_ralt)       /**< Any Alt key is down. */
    #define yk_kmod_gui    (yk_kmod_lgui | yk_kmod_rgui)       /**< Any GUI key is down. */
}
