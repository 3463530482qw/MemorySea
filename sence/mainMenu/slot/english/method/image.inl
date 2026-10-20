namespace Gnik_luos {
    const std::string* Slot::image(std::string_view name) const {   // 命令层按名字拿路径:没这条给空
        const std::string key{name};
        auto it = images.find(key);
        return it == images.end() ? nullptr : &it->second;
    }
}
