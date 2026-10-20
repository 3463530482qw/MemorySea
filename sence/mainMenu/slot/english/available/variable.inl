std::unordered_map<std::string, std::string> images{};   // 图片资源:名字 -> 素材路径,像素归图片模块的缓存
std::unordered_map<std::string, std::unique_ptr<Font>> fonts{};   // 字体资源:名字 -> 字体对象
