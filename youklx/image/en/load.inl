namespace youklx {
    Image& Image::load(const char* path) {
        Plimage img;
        img.data = stbi_load(path, &img.w, &img.h, nullptr, 4);
        if (!img.data) {
            throw std::runtime_error(std::string("图片加载失败: ") + path + " (" + stbi_failure_reason() + ")");
        }
        ima.emplace_back();         //每次 load 新建一个分组
        ima.back().push_back(img);
        return *this;
    }
}