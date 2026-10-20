namespace Gnik_luos {
    Slot& Slot::image_batch_load(Image& image, const simdjson::dom::element& json) {   // 图片段:名字 -> { path }
        simdjson::dom::object body{};
        if (!private_group(json, "image", body)) {
            return *this;
        }
        for (auto field : body) {
            image_load(image, field.value, field.key);
        }
        return *this;
    }

    Slot& Slot::image_load(Image& image, const simdjson::dom::element& json, std::string_view name) {   // path 空着就跳过:槽位留着等素材
        std::string path{};
        if (json["path"].get_string().get(path) || path.empty()) {
            return *this;
        }
        image.find(path);   // 先解一次:路径不对当场报错,像素归图片模块的缓存
        images[std::string(name)] = path;
        return *this;
    }
}
