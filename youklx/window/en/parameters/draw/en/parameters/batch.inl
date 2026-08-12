namespace youklx {
    struct Batch {                     // 顶点段:一段连续顶点属于哪个字体图集
        Font* font{nullptr};           // 字体对象(贴图+图集数据源)
        size_t offset{0};              // 段在顶点流中的起始
        size_t count{0};               // 段顶点数
    };
}
