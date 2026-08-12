vk::raii::PhysicalDevice* physicalDevice{nullptr};
vk::raii::Device* device{nullptr};
vk::raii::RenderPass* renderPass{nullptr};
vk::Format* format{nullptr};
vk::Extent2D* extent{nullptr};
Camera* camera{nullptr};                   // 相机(投影变换用,由窗口注入)
uint32_t graphicsFamilyIndex{0};           // 图形队列族(顶点缓冲分配用)
// 描述符(管线配套资源:布局+池+采样器,图集贴图在 Font 类内)
vk::raii::DescriptorSetLayout descLayout{nullptr};
vk::raii::DescriptorPool descPool{nullptr};
vk::raii::Sampler sampler{nullptr};
// 管线
vk::raii::PipelineLayout pipelineLayout{nullptr};
vk::raii::Pipeline pipeline{nullptr};
// 顶点缓冲(双缓冲:GPU 读上一帧时 CPU 写下一帧,避免撕裂)
std::array<vk::raii::Buffer, 2> vertexBuffer{nullptr, nullptr};
std::array<vk::raii::DeviceMemory, 2> vertexMemory{nullptr, nullptr};
uint32_t vertexFrame{0};   // 当前使用哪个缓冲
// 本帧渲染段(prepare 构建,draw 纯录制;上传必须在录制外,故拆两阶段)
std::vector<Batch> segments;
FontPushConsts pc{};
