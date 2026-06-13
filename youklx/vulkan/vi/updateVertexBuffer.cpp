namespace youklx {

uint32_t Vulkan::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties) {
    vk::PhysicalDeviceMemoryProperties memProperties = this->physicalDevice->getMemoryProperties();
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) &&
            (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }
    throw std::runtime_error("找不到合适的内存类型");
}

Vulkan& Vulkan::updateVertexBuffer(const std::vector<float>& vertices) {
    vk::DeviceSize bufferSize = sizeof(float) * vertices.size();
    this->vertexCount = static_cast<uint32_t>(vertices.size() / 8);

    if (this->vertexCount == 0) {
        // 等待 GPU 完成当前工作后清理顶点缓冲
        if (!this->inFlightFences.empty()) {
            std::vector<vk::Fence> fences;
            fences.reserve(this->inFlightFences.size());
            for (auto& f : this->inFlightFences) {
                fences.push_back(*f);
            }
            auto _ = (*this->device).waitForFences(fences, VK_TRUE, 2'000'000'000);
        }
        this->vertexBuffer.reset();
        this->vertexBufferMemory.reset();
        return *this;
    }

    bool needRecreate = !this->vertexBuffer ||
        this->vertexBuffer->getMemoryRequirements().size < bufferSize;

    if (needRecreate) {
        // 等待所有在途 GPU 工作完成后再销毁旧顶点缓冲
        if (!this->inFlightFences.empty()) {
            std::vector<vk::Fence> fences;
            fences.reserve(this->inFlightFences.size());
            for (auto& f : this->inFlightFences) {
                fences.push_back(*f);
            }
            auto _ = (*this->device).waitForFences(fences, VK_TRUE, 2'000'000'000);
        }
        this->vertexBuffer.reset();
        this->vertexBufferMemory.reset();

        vk::BufferCreateInfo bufferInfo{
            {}, bufferSize,
            vk::BufferUsageFlagBits::eVertexBuffer,
            vk::SharingMode::eExclusive};
        this->vertexBuffer.emplace(*this->device, bufferInfo);

        vk::MemoryRequirements memReqs =
            this->vertexBuffer->getMemoryRequirements();
        uint32_t memType = findMemoryType(
            memReqs.memoryTypeBits,
            vk::MemoryPropertyFlagBits::eHostVisible |
                vk::MemoryPropertyFlagBits::eHostCoherent);

        this->vertexBufferMemory.emplace(
            *this->device,
            vk::MemoryAllocateInfo{memReqs.size, memType});
        this->vertexBuffer->bindMemory(*this->vertexBufferMemory, 0);
    }

    // 等待上一帧提交的 GPU 工作完成，防止覆盖 GPU 正在读取的顶点数据
    // drawFrame 结束后 currentFrame 已推进，上一帧索引 = (currentFrame + MAX-1) % MAX
    if (!this->inFlightFences.empty()) {
        uint32_t prevFrame = (this->currentFrame == 0) ? (MAX_FRAMES_IN_FLIGHT - 1) : (this->currentFrame - 1);
        auto fenceResult = (*this->device).waitForFences(
            {*this->inFlightFences[prevFrame]}, VK_TRUE, 3'000'000'000);
        if (fenceResult == vk::Result::eTimeout) {
            std::cerr << "Vulkan: updateVertexBuffer waitForFences 超时，跳过本帧上传" << std::endl;
            return *this;
        }
    }

    void* data = this->vertexBufferMemory->mapMemory(0, bufferSize);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    this->vertexBufferMemory->unmapMemory();

    return *this;
}

}