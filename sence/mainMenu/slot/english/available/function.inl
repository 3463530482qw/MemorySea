Slot& load(Image& image, const simdjson::dom::element& json);   // 读整份资源表:图片段与字体段
Slot& image_batch_load(Image& image, const simdjson::dom::element& json);   // 图片段整段读
Slot& image_load(Image& image, const simdjson::dom::element& json, std::string_view name);   // 单条图片:名字 -> { path }
Slot& font_batch_load(const simdjson::dom::element& json);   // 字体段整段读
Slot& font_load(const simdjson::dom::element& json, std::string_view name);   // 单条字体:名字 -> { path }
const std::string* image(std::string_view name) const;   // 按名字取图片路径:没这条给空
Font* font(std::string_view name) const;   // 按名字取字体:没这条给空
void clear();
