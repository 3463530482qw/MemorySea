namespace youklx {
    void Ini::add(std::string ini, std::string name) {
        INIReader reader(ini);
        if (reader.ParseError() < 0)
            throw std::runtime_error(std::string("配置文件解析失败: ") + ini);
        // insert_or_assign:同名重复添加时整体替换(支持热重载配置)
        // std::move 避免 INIReader 内部 map 被拷贝
        data.insert_or_assign(std::move(name), std::move(reader));
    }
    void Ini::remove(std::string name) {
        // erase 立即销毁该 INIReader,精确释放内存(capacity 不会残留)
        data.erase(name);
    }
    const INIReader& Ini::get(const std::string& name) const {
        // 按名查找配置,找不到就报错
        auto it = data.find(name);
        if (it == data.end())
            throw std::runtime_error("配置文件不存在: " + name);
        return it->second;
    }
}
