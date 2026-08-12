void load(const char* ttfpath);
void px(float ssize);
Glyph query(char32_t ch);
// --- GPU 图集贴图(贴图待在字体类里,由字体渲染管线在首次绘制时惰性初始化) ---
bool rendererBound() const;   // 贴图是否已绑定渲染端
void bindRenderer(vk::raii::PhysicalDevice& pd, vk::raii::Device& dev,
                  vk::raii::DescriptorSetLayout& layout, vk::raii::DescriptorPool& pool,
                  vk::raii::Sampler& samp, uint32_t queueFamilyIndex);
void uploadAtlas();                        // 图集版本变化时上传(一次性命令池)
vk::DescriptorSet descriptorSet() const;   // 描述符集句柄(渲染端绑定图集用)
