void 添加(std::string 名字, Font* 字体) { add(std::move(名字), 字体); }
void 移除(std::string 名字) { remove(std::move(名字)); }
Font* 取(const std::string& 名字) const { return get(名字); }
Fontmap& 初始化配置(const INIReader& 配置读取器, const std::string& 标签) { return iload(配置读取器, 标签); }
