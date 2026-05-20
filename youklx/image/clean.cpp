namespace youklx {
    Image& Image::clean() {
        if(ima.empty()) {
            std::cout << "There's no picture right now, what the hell are you cleaning, you bastard Ծ‸Ծ" << std::endl;
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