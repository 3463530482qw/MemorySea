namespace youklx {
    void FontRender::init(vk::raii::PhysicalDevice& pd, vk::raii::Device& dev, vk::raii::RenderPass& rp, vk::Format& fmt, vk::Extent2D& ext, Font* fot, uint32_t queueFamilyIndex) {
        physicalDevice = &pd;
        device = &dev;
        renderPass = &rp;
        format = &fmt;
        extent = &ext;
        font = fot;
        graphicsFamilyIndex = queueFamilyIndex;
        createTexture();
        createPipeline();
        createVertexBuffer();
    }
}
