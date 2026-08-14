namespace youklx {
    void Fontmap::add(std::string name, Font* font) {
        // insert_or_assign:同名重复注册时整体替换(支持热更新字体绑定)
        data.insert_or_assign(std::move(name), font);
    }
    void Fontmap::remove(std::string name) {
        // erase 只移除登记,不销毁字体对象(字体生命周期归场景管理)
        data.erase(name);
    }
    Font* Fontmap::get(const std::string& name) const {
        // 按名查找字体,找不到就报错
        auto it = data.find(name);
        if (it == data.end())
            throw std::runtime_error("字体不存在: " + name);
        return it->second;
    }
}
