namespace youklx {
    // 图集版本变化时上传(一次性命令池执行过渡+copy,提交后等待;调用须在命令缓冲录制外)
    void Font::uploadAtlas() {
        if (!device || atlas.empty() || uploadedVersion == atlasVersion) return;
        if (uploadedW != atlasW || uploadedH != atlasH) recreateTexture();
        uploadedVersion = atlasVersion;

        // 一次性命令池 + 缓冲
        vk::CommandPoolCreateInfo poolInfo;
        poolInfo.setFlags(vk::CommandPoolCreateFlagBits::eTransient);
        vk::raii::CommandPool pool(*device, poolInfo);
        vk::CommandBufferAllocateInfo allocInfo;
        allocInfo.setCommandPool(*pool);
        allocInfo.setLevel(vk::CommandBufferLevel::ePrimary);
        allocInfo.setCommandBufferCount(1);
        vk::raii::CommandBuffer cmd = std::move(vk::raii::CommandBuffers(*device, allocInfo)[0]);

        // 暂存缓冲(host-visible)拷贝图集数据
        size_t atlasBytes = static_cast<size_t>(atlasW) * atlasH;
        vk::BufferCreateInfo stageInfo;
        stageInfo.setSize(atlasBytes);
        stageInfo.setUsage(vk::BufferUsageFlagBits::eTransferSrc);
        stageInfo.setSharingMode(vk::SharingMode::eExclusive);
        vk::raii::Buffer stageBuf(*device, stageInfo);
        vk::MemoryRequirements memReq = stageBuf.getMemoryRequirements();
        vk::MemoryAllocateInfo stageAlloc;
        stageAlloc.setAllocationSize(memReq.size);
        stageAlloc.setMemoryTypeIndex(findMemoryType(*physicalDevice, memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));
        vk::raii::DeviceMemory stageMem(*device, stageAlloc);
        stageBuf.bindMemory(*stageMem, 0);
        void* mapped = stageMem.mapMemory(0, atlasBytes);
        std::memcpy(mapped, atlas.data(), atlasBytes);
        stageMem.unmapMemory();

        // 录制:过渡 + copy + 过渡到 shader-read
        vk::CommandBufferBeginInfo beginInfo;
        beginInfo.setFlags(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
        cmd.begin(beginInfo);

        vk::ImageMemoryBarrier toDst;
        toDst.setOldLayout(vk::ImageLayout::eUndefined);
        toDst.setNewLayout(vk::ImageLayout::eTransferDstOptimal);
        toDst.setSrcQueueFamilyIndex(vk::QueueFamilyIgnored);
        toDst.setDstQueueFamilyIndex(vk::QueueFamilyIgnored);
        toDst.setImage(*atlasImage);
        toDst.setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
        toDst.setSrcAccessMask(vk::AccessFlagBits::eNone);
        toDst.setDstAccessMask(vk::AccessFlagBits::eTransferWrite);
        cmd.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer,
            {}, {}, {}, {toDst});

        vk::BufferImageCopy region;
        region.setBufferOffset(0);
        region.setBufferRowLength(static_cast<uint32_t>(atlasW));
        region.setBufferImageHeight(static_cast<uint32_t>(atlasH));
        region.setImageSubresource(vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1));
        region.setImageOffset(vk::Offset3D{0, 0, 0});
        region.setImageExtent(vk::Extent3D{static_cast<uint32_t>(atlasW), static_cast<uint32_t>(atlasH), 1});
        cmd.copyBufferToImage(*stageBuf, *atlasImage, vk::ImageLayout::eTransferDstOptimal, {region});

        vk::ImageMemoryBarrier toRead;
        toRead.setOldLayout(vk::ImageLayout::eTransferDstOptimal);
        toRead.setNewLayout(vk::ImageLayout::eShaderReadOnlyOptimal);
        toRead.setSrcQueueFamilyIndex(vk::QueueFamilyIgnored);
        toRead.setDstQueueFamilyIndex(vk::QueueFamilyIgnored);
        toRead.setImage(*atlasImage);
        toRead.setSubresourceRange(vk::ImageSubresourceRange(vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1));
        toRead.setSrcAccessMask(vk::AccessFlagBits::eTransferWrite);
        toRead.setDstAccessMask(vk::AccessFlagBits::eShaderRead);
        cmd.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eFragmentShader,
            {}, {}, {}, {toRead});

        cmd.end();

        // 提交并等待(图形队列)
        VkDevice vkd = **device;   // 指针成员:解指针得 raii,再解得句柄
        VkQueue vkq;
        vkGetDeviceQueue(vkd, graphicsFamilyIndex, 0, &vkq);
        VkSubmitInfo submit{};
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit.commandBufferCount = 1;
        VkCommandBuffer cmdHandle = *cmd;
        submit.pCommandBuffers = &cmdHandle;
        if (vkQueueSubmit(vkq, 1, &submit, VK_NULL_HANDLE) != VK_SUCCESS)
            throw std::runtime_error("图集上传提交失败");
        vkQueueWaitIdle(vkq);
    }
}
