namespace youklx {
    class Vulkan {
    public:
        vk::raii::Context context;                        // Vulkan 上下文，管理加载器
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

        std::vector<vk::raii::Semaphore> imageAvailableSemaphores;  // 信号量：图像获取完成
        std::vector<vk::raii::Semaphore> renderFinishedSemaphores;  // 信号量：渲染完成
        std::vector<vk::raii::Fence> inFlightFences;                // 围栏：CPU等待GPU
        uint32_t currentFrame = 0;                        // 当前帧索引

        std::optional<vk::raii::PipelineLayout> pipelineLayout; // 管线布局
        std::optional<vk::raii::Pipeline> graphicsPipeline;      // 图形管线
    public:
        int stsizew{}; // 交换链逻辑大小宽度
        int stsizeh{}; // 交换链逻辑大小高度
    public:
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
        
        Vulkan& drawFrame();                              // 渲染一帧
        Vulkan& init(Window& window);                     // 初始化
        Vulkan& recreateSwapChain();   // 重建交换链
    public:
        uint32_t ratePhysicalDevice(                      // 对指定物理设备进行评分
            const vk::raii::PhysicalDevice& device
        );
        Vulkan& recordCommandBuffer(uint32_t imageIndex); // 记录命令缓冲
    public:
        Vulkan& lstsize(int w, int h);
        Vulkan& ilstsize(std::string ini, std::string ivrtp, std::string witp, std::string hitp);
    };
}

#include "vl/createInstance.cpp"
#include "vl/pickPhysicalDevice.cpp"
#include "vl/findGraphicsQueueFamily.cpp"
#include "vl/createDevice.cpp"
#include "vl/createSurface.cpp"
#include "vl/createSwapChain.cpp"
#include "vl/createRenderPass.cpp"
#include "vl/createFramebuffers.cpp"
#include "vl/createCommandPool.cpp"
#include "vl/createCommandBuffers.cpp"
#include "vl/createSyncObjects.cpp"
#include "vl/recordCommandBuffer.cpp"
#include "vl/drawFrame.cpp"
#include "vl/init.cpp"
#include "vl/createPipeline.cpp"
#include "vl/recreateSwapChain.cpp"
#include "vi/lstsize.cpp"