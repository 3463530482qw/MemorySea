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
        this->device->waitIdle();
        this->vertexBuffer.reset();
        this->vertexBufferMemory.reset();
        return *this;
    }

    bool needRecreate = !this->vertexBuffer ||
        this->vertexBuffer->getMemoryRequirements().size < bufferSize;

    if (needRecreate) {
        this->device->waitIdle();
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

    void* data = this->vertexBufferMemory->mapMemory(0, bufferSize);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    this->vertexBufferMemory->unmapMemory();

    return *this;
}

}