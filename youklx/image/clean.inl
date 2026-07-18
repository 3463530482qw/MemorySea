namespace youklx {
    Image& Image::clean() {
        for (auto& arima : ima) {
            for (auto& image : arima) {
                auto& cima = std::visit(std::identity{}, image);
                stbi_image_free(cima.data);
                cima.data = nullptr;
            }
        }
        ima.clear();
        atlasData.clear();
        atlasW = 0;
        atlasH = 0;
        return *this;
    }
}
