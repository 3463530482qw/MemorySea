void init(vk::raii::PhysicalDevice& pd, vk::raii::Device& dev, vk::raii::RenderPass& rp, vk::Format& fmt, vk::Extent2D& ext, Font* fot, uint32_t queueFamilyIndex);
void draw(vk::raii::CommandBuffer& cmdbuf, const std::vector<Vertex>& vertices, float screenW, float screenH);
void createTexture();
void recreateTexture();
void createPipeline();
void createVertexBuffer();
void uploadAtlas();
uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags flags) const;
