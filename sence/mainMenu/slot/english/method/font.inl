namespace Gnik_luos {
    Font* Slot::font(std::string_view name) const {   // 命令层按名字拿字体:没这条给空
        const std::string key{name};
        auto it = fonts.find(key);
        return it == fonts.end() ? nullptr : it->second.get();
    }
}
