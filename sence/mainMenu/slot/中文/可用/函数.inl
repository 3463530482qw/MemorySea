Slot& 装载(Image& image, const simdjson::dom::element& json) { return load(image, json); }
void 清空() { clear(); }
const std::string* 获取图片(std::string_view name) const { return image(name); }
Font* 获取字体(std::string_view name) const { return font(name); }
