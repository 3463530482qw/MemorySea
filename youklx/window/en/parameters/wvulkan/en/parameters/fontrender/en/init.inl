namespace youklx {
    void FontRender::init(vk::raii::PhysicalDevice& pd, vk::raii::Device& dev, vk::raii::RenderPass& rp, vk::Format& fmt, vk::Extent2D& ext, uint32_t queueFamilyIndex) {
        physicalDevice = &pd;
        device = &dev;
        renderPass = &rp;
        format = &fmt;
        extent = &ext;
        graphicsFamilyIndex = queueFamilyIndex;
        createDescriptors();
        createPipeline();
        createVertexBuffer();
    }
}
