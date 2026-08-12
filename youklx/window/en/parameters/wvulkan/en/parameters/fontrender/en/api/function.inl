void init(vk::raii::PhysicalDevice& pd, vk::raii::Device& dev, vk::raii::RenderPass& rp, vk::Format& fmt, vk::Extent2D& ext, uint32_t queueFamilyIndex);
// 录制前准备:构建渲染段、惰性初始化贴图、上传图集与顶点(内含提交+等待,必须在录制外)
void prepare(const std::vector<Batch>& batches, const std::vector<Vertex>& vertices,
             Font& defaultFont, float screenW, float screenH);
// 纯录制:按 prepare 构建的段绑定图集描述符并绘制
void draw(vk::raii::CommandBuffer& cmdbuf);
void createDescriptors();
void createPipeline();
void createVertexBuffer();
