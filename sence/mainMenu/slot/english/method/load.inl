namespace Gnik_luos {
    Slot& Slot::load(Image& image, const simdjson::dom::element& json) {   // 先清空再装:重装不会留旧条目
        clear();
        image_batch_load(image, json);
        font_batch_load(json);
        return *this;
    }
}
