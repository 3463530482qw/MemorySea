namespace youklx {
    Image& Image::clean() {
        if(ima.empty()) {
            std::cout << "The picture is empty, this is terrible, I am crying in panic Ծ‸Ծ" << std::endl;
        } else {
            for (auto& arima : ima) {
                for (auto& image : arima) {
                    auto& cima = std::visit(std::identity{}, image);
                    stbi_image_free(cima.data);
                    cima.data = nullptr;
                }
            }
            ima.clear();
        }
        return *this;
    }
}