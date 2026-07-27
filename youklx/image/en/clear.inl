namespace youklx {
    Image& Image::clear() {
        for (auto& group : ima) {
            for (auto& img : group) {
                if (img.data) {
                    stbi_image_free(img.data);
                    img.data = nullptr;
                }
            }
        }
        ima.clear();
        return *this;
    }
}
