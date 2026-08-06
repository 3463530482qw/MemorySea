void 添加(std::string ini, std::string name) { add(std::move(ini), std::move(name)); }
void 移除(std::string name) { remove(std::move(name)); }
const INIReader& 取(const std::string& 名字) const { return get(名字); }
