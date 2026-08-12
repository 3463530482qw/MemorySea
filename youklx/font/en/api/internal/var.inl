// --- GPU 图集贴图资源(生命周期:依赖渲染端 device 存活,字体须先于窗口销毁) ---
vk::raii::Image atlasImage{nullptr};
vk::raii::DeviceMemory atlasMemory{nullptr};
vk::raii::ImageView atlasView{nullptr};
vk::raii::DescriptorSet descSet{nullptr};   // raii 持有所有权,析构时释放回池
// 上传快照(渲染侧据此检测图集变化)
uint64_t uploadedVersion{0};
int uploadedW{0}, uploadedH{0};
// 渲染端引用(惰性注入;句柄不管理生命周期)
vk::raii::PhysicalDevice* physicalDevice{nullptr};
vk::raii::Device* device{nullptr};
vk::DescriptorSetLayout descLayout{};   // 描述符布局句柄
vk::DescriptorPool descPool{};          // 描述符池句柄(描述符集归池所有)
vk::Sampler sampler{};                  // 采样器句柄
uint32_t graphicsFamilyIndex{0};
