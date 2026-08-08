vk::raii::PhysicalDevice* physicalDevice{nullptr};
vk::raii::Device* device{nullptr};
vk::raii::RenderPass* renderPass{nullptr};
vk::Format* format{nullptr};
vk::Extent2D* extent{nullptr};
Font* font{nullptr};                       // 绑定的字体对象(图集数据源)
Camera* camera{nullptr};                   // 相机(投影变换用,由 wvulkan 注入)
uint32_t graphicsFamilyIndex{0};           // 图形队列族(上传用)
uint64_t atlasVersion{0};                  // 已上传图集版本快照
int atlasW{1024}, atlasH{1024};            // 已上传图集尺寸(变化时重建纹理)
// 图集纹理
vk::raii::Image atlasImage{nullptr};
vk::raii::DeviceMemory atlasMemory{nullptr};
vk::raii::ImageView atlasView{nullptr};
vk::raii::Sampler sampler{nullptr};
// 描述符
vk::raii::DescriptorSetLayout descLayout{nullptr};
vk::raii::DescriptorPool descPool{nullptr};
vk::raii::DescriptorSet descSet{nullptr};
// 管线
vk::raii::PipelineLayout pipelineLayout{nullptr};
vk::raii::Pipeline pipeline{nullptr};
// 顶点缓冲(双缓冲:GPU 读上一帧时 CPU 写下一帧,避免撕裂)
std::array<vk::raii::Buffer, 2> vertexBuffer{nullptr, nullptr};
std::array<vk::raii::DeviceMemory, 2> vertexMemory{nullptr, nullptr};
uint32_t vertexFrame{0};   // 当前使用哪个缓冲
