namespace youklx {
    Image& Image::lpng(const char* image) {
        ima.push_back(std::vector<Plimage>());
        Plpng imapng;
        imapng.data = stbi_load(image, &imapng.w, &imapng.h, &imapng.channels, imapng.desired_channels);
        
        
        if (imapng.data == nullptr) {
            std::cerr << "加载图片失败: " << stbi_failure_reason() << std::endl;
        } else {
            ima.back().push_back(imapng);
        }
        return *this;
    }
}