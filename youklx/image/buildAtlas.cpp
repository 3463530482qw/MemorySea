namespace youklx {

Image& Image::buildAtlas() {
    atlasData.clear();
    atlasW = 0;
    atlasH = 0;
    if (ima.empty()) return *this;

    // 计算所有图片总高度（水平拼接：所有图片放在一行）
    int totalW = 0;
    int maxH = 0;
    for (auto& group : ima) {
        for (auto& imgvar : group) {
            Plpng* png = nullptr;
            if (std::holds_alternative<Plpng>(imgvar)) {
                png = &std::get<Plpng>(imgvar);
            }
            if (!png || !png->data || png->w <= 0 || png->h <= 0) continue;
            totalW += png->w;
            if (png->h > maxH) maxH = png->h;
        }
    }
    if (totalW == 0 || maxH == 0) return *this;

    atlasW = totalW;
    atlasH = maxH;
    atlasData.resize(atlasW * atlasH * 4, 0);

    int curX = 0;
    for (auto& group : ima) {
        for (auto& imgvar : group) {
            Plpng* png = nullptr;
            if (std::holds_alternative<Plpng>(imgvar)) {
                png = &std::get<Plpng>(imgvar);
            }
            if (!png || !png->data || png->w <= 0 || png->h <= 0) continue;

            // 设置图集 UV
            png->u0 = (float)curX / (float)atlasW;
            png->v0 = 0.0f;
            png->u1 = (float)(curX + png->w) / (float)atlasW;
            png->v1 = (float)png->h / (float)atlasH;

            // 拷贝像素到图集
            for (int row = 0; row < png->h; ++row) {
                int srcOff = row * png->w * 4;
                int dstOff = (row * atlasW + curX) * 4;
                memcpy(atlasData.data() + dstOff, png->data + srcOff, png->w * 4);
            }
            curX += png->w;
        }
    }

    return *this;
}

} // namespace youklx