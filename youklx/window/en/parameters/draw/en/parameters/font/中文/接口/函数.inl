Fontcmd& 设字体(Font* 字体) { return sf(字体); }
Fontcmd& 设文字(std::string 文字内容) { return sc(文字内容); }
Fontcmd& 设位置(float 位置x, float 位置y) { return sp(位置x, 位置y); }
Fontcmd& 设字号(float 字号) { return ss(字号); }
Fontcmd& 设旋转(float 角度, float 中心x, float 中心y) { return srot(角度, 中心x, 中心y); }
Fontcmd& 设颜色(std::array<float, 4> 颜色值) { return srgba(颜色值); }
Fontcmd& 设顺序(int 顺序) { return so(顺序); }
Fontcmd& 设描边(bool 是否开启, float 宽度, std::array<float, 4> 颜色值) { return soutline(是否开启, 宽度, 颜色值); }
Fontcmd& 初始化配置(const Fontmap& 字体表, const INIReader& 配置读取器, const std::string& 标签) { return iload(字体表, 配置读取器, 标签); }
