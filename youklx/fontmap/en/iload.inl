namespace youklx {
    // 通过标签装载字体:[ivrtp.名字] 一节一个字体,节内 名字 = ttf路径,px = 烘焙字号(可缺省)
    Fontmap& Fontmap::iload(const INIReader& reader, const std::string& ivrtp) {
        const std::string prefix = ivrtp + ".";

        // 收集所有字体标签,标签名去掉前缀即字体名
        std::vector<std::string> names;
        for (const std::string& sec : reader.Sections()) {
            if (sec.size() > prefix.size() && sec.compare(0, prefix.size(), prefix) == 0)
                names.push_back(sec.substr(prefix.size()));
        }

        // 热更新:先注销并销毁上一批 iload 创建的字体,再整批重建
        for (const std::string& name : owned_names) remove(name);
        owned_names.clear();
        owned.clear();

        for (const std::string& name : names) {
            std::string path = reader.Get(prefix + name, name, "");
            if (path.empty())
                throw std::runtime_error("字体缺路径: " + name);
            auto font = std::make_unique<Font>();
            font->load(path.c_str());
            float pxv = static_cast<float>(reader.GetReal(prefix + name, "px", 0.0));
            if (pxv > 0.0f) font->px(pxv);
            add(name, font.get());
            owned_names.push_back(name);
            owned.push_back(std::move(font));
        }
        return *this;
    }
}
