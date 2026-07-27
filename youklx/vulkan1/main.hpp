namespace youklx {
    class Vulkan {
    public:
        ~Vulkan() {
            if (this->device) {
                this->device->waitIdle();
            }
        }
    public:
    vk::raii::Context context;
        std::optional<vk::raii::Instance> instance;       // Vulkan 实例，连接驱动
        std::optional<vk::raii::PhysicalDevice> physicalDevice; // 物理设备，代表GPU

        uint32_t graphicsFamilyIndex;                     // 图形队列族索引
        std::optional<vk::raii::Device> device;           // 逻辑设备，用于资源创建与命令执行
        std::optional<vk::raii::Queue> graphicsQueue;     // 图形队列，提交渲染命令
        std::optional<vk::raii::SurfaceKHR> surface;      // 窗口表面，对接操作系统窗口

        std::optional<vk::raii::SwapchainKHR> swapChain;  // 交换链，管理呈现用图像
        vk::Format swapChainImageFormat;                  // 交换链图像格式
        vk::Extent2D swapChainExtent;                     // 交换链图像尺寸
        std::vector<vk::Image> swapChainImages;                   // 交换链图像
        std::vector<vk::raii::ImageView> swapChainImageViews; // 交换链图像视图

        std::optional<vk::raii::RenderPass> renderPass;   // 渲染通道，描述附件用法
        std::vector<vk::raii::Framebuffer> swapChainFramebuffers; // 帧缓冲，每张交换链图像一个
        std::optional<vk::raii::CommandPool> commandPool; // 命令池，分配命令缓冲
        std::vector<vk::raii::CommandBuffer> commandBuffers; // 命令缓冲，每帧一个
        static constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 2; // 最大并行帧数

        std::vector<vk::raii::Semaphore> imageAvailableSemaphores;  // 信号量：图像获取完成 (MAX_FRAMES_IN_FLIGHT)
        std::vector<vk::raii::Semaphore> renderFinishedSemaphores;  // 信号量：渲染完成 (per swapchain image)
        std::vector<vk::raii::Fence> inFlightFences;                // 围栏：CPU等待GPU (MAX_FRAMES_IN_FLIGHT)
        uint32_t currentFrame = 0;                        // 当前帧索引 (0..MAX_FRAMES_IN_FLIGHT-1)

        std::optional<vk::raii::PipelineLayout> pipelineLayout;       // 管线布局
        std::optional<vk::raii::Pipeline> graphicsPipeline;            // 线条管线
        std::optional<vk::raii::Pipeline> graphicsPipelineImage;       // 图片管线
        std::optional<vk::raii::Pipeline> graphicsPipelineFont;        // 字体管线
        std::optional<vk::raii::DescriptorSetLayout> descSetLayout;   // 描述符布局
        std::optional<vk::raii::DescriptorPool> descPool;             // 描述符池
        std::optional<vk::raii::Image> dummyImage;                    // 默认 1x1 纹理
        std::optional<vk::raii::DeviceMemory> dummyImageMemory;       // 默认纹理内存
        std::optional<vk::raii::ImageView> dummyImageView;            // 默认纹理视图
        std::optional<vk::raii::Sampler> dummySampler;                // 默认采样器
        std::optional<vk::raii::DescriptorSet> descSet;               // 描述符集（图片）
        bool textureBuilt{false};                                      // 纹理是否已构建（避免每帧重建）

        // 字体纹理资源
        std::optional<vk::raii::Image> fontImage;                     // 字体图集图像
        std::optional<vk::raii::DeviceMemory> fontImageMemory;        // 字体图集内存
        std::optional<vk::raii::ImageView> fontImageView;             // 字体图集视图
        std::optional<vk::raii::Sampler> fontSampler;                 // 字体图集采样器
        std::optional<vk::raii::DescriptorSet> fontDescSet;           // 字体描述符集

        // 顶点缓冲
        std::optional<vk::raii::Buffer> vertexBuffer;      // 顶点缓冲
        std::optional<vk::raii::DeviceMemory> vertexBufferMemory; // 顶点缓冲内存
        uint32_t vertexCount{0};                            // 当前顶点数量
    public:
        int stsizew{}; // 交换链逻辑大小宽度
        int stsizeh{}; // 交换链逻辑大小高度

        // viewport 参数（在 recordCommandBuffer 中计算，供 Window::run() 做鼠标坐标转换）
        int viewportX{0};
        int viewportY{0};
        int viewportW{0};
        int viewportH{0};
        // MSAA 多样本抗锯齿（默认 1 = 关闭，设为 4 = 4x MSAA，必须在 init 前调用）
        vk::SampleCountFlagBits msaaSamples{vk::SampleCountFlagBits::e1};
        // MSAA 图像（每帧一个，与交换链图像一一对应）
        std::vector<vk::raii::Image> msaaImages;
        std::vector<vk::raii::DeviceMemory> msaaMemories;
        std::vector<vk::raii::ImageView> msaaViews;
        // 像素完美模式：最近邻采样 + 顶点对齐像素网格
        bool pixelPerfect{false};
    public:
        Vulkan& msaa(int samples);                       // 设置 MSAA 采样数
        // pixelPerfect 直接赋值：vulkan.pixelPerfect = true;
        Vulkan& createInstance();                         // 创建实例
        Vulkan& pickPhysicalDevice();                     // 选择物理设备
        
        Vulkan& findGraphicsQueueFamily();                // 查找图形队列族
        Vulkan& createDevice();                           // 创建逻辑设备与图形队列
        Vulkan& createSurface(SDL_Window* window);        // 创建窗口表面，传入SDL窗口
        Vulkan& createSwapChain();                        // 创建交换链
        Vulkan& createRenderPass();                       // 创建渲染通道
        Vulkan& createFramebuffers();                     // 创建帧缓冲
        Vulkan& createCommandPool();                      // 创建命令池
        Vulkan& createCommandBuffers();                   // 创建命令缓冲
        Vulkan& createSyncObjects();                      // 创建同步对象
        Vulkan& createPipeline();                                // 创建图形管线
        
        Vulkan& drawFrame(Draw& draw);                              // 渲染一帧
        Vulkan& init(Window& window);                     // 初始化
        Vulkan& recreateSwapChain();   // 重建交换链
    public:
        uint32_t ratePhysicalDevice(                      // 对指定物理设备进行评分
            const vk::raii::PhysicalDevice& device
        );
        Vulkan& recordCommandBuffer(uint32_t imageIndex, Draw& draw); // 记录命令缓冲
        Vulkan& updateVertexBuffer(const std::vector<float>& vertices); // 更新顶点缓冲
        Vulkan& updateTexture(Image& img);                  // 更新纹理图集
        Vulkan& updateFontTexture(Font* font);              // 更新字体图集纹理
        uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);
    public:
        Vulkan& lstsize(int w, int h);
        Vulkan& ilstsize(std::string ini, std::string ivrtp, std::string witp, std::string hitp);
    };
}

#include "vl/createInstance.inl"
#include "vl/pickPhysicalDevice.inl"
#include "vl/findGraphicsQueueFamily.inl"
#include "vl/createDevice.inl"
#include "vl/createSurface.inl"
#include "vl/createSwapChain.inl"
#include "vl/createRenderPass.inl"
#include "vl/createFramebuffers.inl"
#include "vl/createCommandPool.inl"
#include "vl/createCommandBuffers.inl"
#include "vl/createSyncObjects.inl"
#include "vl/recordCommandBuffer.inl"
#include "vl/drawFrame.inl"
#include "vl/init.inl"
#include "vl/createPipeline.inl"
#include "vl/recreateSwapChain.inl"
#include "vi/lstsize.inl"
#include "vi/updateVertexBuffer.inl"
#include "vi/updateTexture.inl"
#include "vi/updateFontTexture.inl"
