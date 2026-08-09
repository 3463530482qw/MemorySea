namespace youklx {
    // --- 顶点缓冲(host-visible,双缓冲,每帧交替 memcpy) ---
    void FontRender::createVertexBuffer() {
        vk::BufferCreateInfo bufInfo;
        bufInfo.setSize(1024 * 1024);                     // 1MB 预分配
        bufInfo.setUsage(vk::BufferUsageFlagBits::eVertexBuffer);
        bufInfo.setSharingMode(vk::SharingMode::eExclusive);
        for (int i = 0; i < 2; i++) {
            vertexBuffer[i] = vk::raii::Buffer(*device, bufInfo);
            vk::MemoryRequirements memReq = vertexBuffer[i].getMemoryRequirements();
            vk::MemoryAllocateInfo allocInfo;
            allocInfo.setAllocationSize(memReq.size);
            allocInfo.setMemoryTypeIndex(findMemoryType(memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));
            vertexMemory[i] = vk::raii::DeviceMemory(*device, allocInfo);
            vertexBuffer[i].bindMemory(*vertexMemory[i], 0);
        }
    }
}
