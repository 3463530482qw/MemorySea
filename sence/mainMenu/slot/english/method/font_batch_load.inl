namespace Gnik_luos {
    Slot& Slot::font_batch_load(const simdjson::dom::element& json) {   // 字体段:名字 -> { path }
        simdjson::dom::object body{};
        if (!private_group(json, "font", body)) {
            return *this;
        }
        for (auto field : body) {
            font_load(field.value, field.key);
        }
        return *this;
    }

    Slot& Slot::font_load(const simdjson::dom::element& json, std::string_view name) {   // path 空着就跳过:槽位留着等素材
        std::string path{};
        if (json["path"].get_string().get(path) || path.empty()) {
            return *this;
        }
        auto& face = fonts[std::string(name)];
        if (!face) {
            face = std::make_unique<Font>();
        }
        face->load(path);
        return *this;
    }
}
