void add(std::string name, Font* font);
void remove(std::string name);
Font* get(const std::string& name) const;
Fontmap& iload(const INIReader& reader, const std::string& ivrtp);
