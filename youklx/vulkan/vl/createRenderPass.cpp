namespace youklx {
    Vulkan& Vulkan::createRenderPass() {
        // 1. 颜色附件描述
        vk::AttachmentDescription colorAttachment{
            {},                                           // flags
            this->swapChainImageFormat,                   // 格式与交换链一致
            vk::SampleCountFlagBits::e1,                  // 采样数
            vk::AttachmentLoadOp::eClear,                 // 加载时清屏
            vk::AttachmentStoreOp::eStore,                // 存储时保留结果
            vk::AttachmentLoadOp::eDontCare,              // 模板加载（不使用）
            vk::AttachmentStoreOp::eDontCare,             // 模板存储（不使用）
            vk::ImageLayout::eUndefined,                  // 初始布局
            vk::ImageLayout::ePresentSrcKHR               // 最终布局：呈现用
        };

        // 2. 颜色附件引用（着色器中对应 location = 0）
        vk::AttachmentReference colorAttachmentRef{
            0,                                            // 附件索引
            vk::ImageLayout::eColorAttachmentOptimal      // 渲染时的布局
        };

        // 3. 子通道描述
        vk::SubpassDescription subpass{
            {},                                           // flags
            vk::PipelineBindPoint::eGraphics,             // 图形管线
            0,                                            // 输入附件数量
            nullptr,                                      // 输入附件
            1,                                            // 颜色附件数量
            &colorAttachmentRef,                          // 颜色附件引用
            nullptr,                                      // 解析附件
            nullptr,                                      // 深度模板附件
            0,                                            // 保留附件数量
            nullptr                                       // 保留附件
        };

        // 4. 子通道依赖（确保渲染顺序）
        vk::SubpassDependency dependency{
            VK_SUBPASS_EXTERNAL,                          // 源子通道
            0,                                            // 目标子通道
            vk::PipelineStageFlagBits::eColorAttachmentOutput, // 源阶段
            vk::PipelineStageFlagBits::eColorAttachmentOutput, // 目标阶段
            {},                                           // 源访问掩码
            vk::AccessFlagBits::eColorAttachmentWrite,    // 目标访问掩码
            {}                                            // 依赖标志
        };

        // 5. 渲染通道创建信息
        vk::RenderPassCreateInfo createInfo{
            {},                                           // flags
            1,                                            // 附件数量
            &colorAttachment,                             // 附件数组
            1,                                            // 子通道数量
            &subpass,                                     // 子通道数组
            1,                                            // 依赖数量
            &dependency                                   // 依赖数组
        };

        // 6. 创建渲染通道
        this->renderPass.emplace(*this->device, createInfo);

        return *this;
    }
}