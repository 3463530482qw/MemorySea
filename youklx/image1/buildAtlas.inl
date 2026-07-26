namespace youklx {

Image& Image::buildAtlas() {
    atlasData.clear();
    atlasW = 0;
    atlasH = 0;
    if (ima.empty()) return *this;

    // 计算所有图片总宽度 + padding（水平拼接，图片间留透明间隔防采样 bleeding）
    constexpr int PADDING = 2;
    int totalW = 0;
    int maxH = 0;
    int imgCount = 0;
    for (auto& group : ima) {
        for (auto& imgvar : group) {
            auto* png = std::get_if<Plpng>(&imgvar);
            if (!png || !png->data || png->w <= 0 || png->h <= 0) continue;
            totalW += png->w;
            if (png->h > maxH) maxH = png->h;
            imgCount++;
        }
    }
    if (totalW == 0 || maxH == 0) return *this;
    // 加上所有图片间的 padding（每张图片后 +PADDING，最后一张不加）
    totalW += PADDING * imgCount;

    atlasW = totalW;
    atlasH = maxH;
    atlasData.resize(atlasW * atlasH * 4, 0);

    int curX = PADDING;  // 左侧留 padding，防止线性采样 bleeding
    for (auto& group : ima) {
        for (auto& imgvar : group) {
            auto* png = std::get_if<Plpng>(&imgvar);
            if (!png || !png->data || png->w <= 0 || png->h <= 0) continue;

            // 设置图集 UV（指向实际图片数据，不含 padding）
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
            curX += png->w + PADDING;
        }
    }

    return *this;
}

} // namespace youklx