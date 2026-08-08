namespace youklx {
    // 图集变化时重传纹理(用一次性命令池执行 copy)
    void FontRender::uploadAtlas() {
        if (!font || atlasVersion == font->atlasVersion) return;
        if (font->atlas.empty()) return;   // 图集还没烘焙(px 刚清空),等下一帧
        atlasVersion = font->atlasVersion;

        // 图集尺寸变化 → 重建纹理(Image/View/Memory)并更新描述符
        if (atlasW != font->atlasW || atlasH != font->atlasH) {
            recreateTexture();
        }

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
        size_t atlasBytes = static_cast<size_t>(font->atlasW) * font->atlasH;
        vk::BufferCreateInfo stageInfo;
        stageInfo.setSize(atlasBytes);
        stageInfo.setUsage(vk::BufferUsageFlagBits::eTransferSrc);
        stageInfo.setSharingMode(vk::SharingMode::eExclusive);
        vk::raii::Buffer stageBuf(*device, stageInfo);
        vk::MemoryRequirements memReq = stageBuf.getMemoryRequirements();
        vk::MemoryAllocateInfo stageAlloc;
        stageAlloc.setAllocationSize(memReq.size);
        stageAlloc.setMemoryTypeIndex(findMemoryType(memReq.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent));
        vk::raii::DeviceMemory stageMem(*device, stageAlloc);
        stageBuf.bindMemory(*stageMem, 0);
        void* mapped = stageMem.mapMemory(0, atlasBytes);
        std::memcpy(mapped, font->atlas.data(), atlasBytes);
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
        region.setBufferRowLength(static_cast<uint32_t>(font->atlasW));
        region.setBufferImageHeight(static_cast<uint32_t>(font->atlasH));
        region.setImageSubresource(vk::ImageSubresourceLayers(vk::ImageAspectFlagBits::eColor, 0, 0, 1));
        region.setImageOffset(vk::Offset3D{0, 0, 0});
        region.setImageExtent(vk::Extent3D{static_cast<uint32_t>(font->atlasW), static_cast<uint32_t>(font->atlasH), 1});
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
        VkDevice vkd = static_cast<VkDevice>(**device);
        VkQueue vkq;
        vkGetDeviceQueue(vkd, graphicsFamilyIndex, 0, &vkq);
        VkSubmitInfo submit{};
        submit.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit.commandBufferCount = 1;
        VkCommandBuffer cmdHandle = static_cast<VkCommandBuffer>(*cmd);
        submit.pCommandBuffers = &cmdHandle;
        if (vkQueueSubmit(vkq, 1, &submit, VK_NULL_HANDLE) != VK_SUCCESS)
            throw std::runtime_error("图集上传提交失败");
        vkQueueWaitIdle(vkq);
    }

    void FontRender::draw(vk::raii::CommandBuffer& cmdbuf, const std::vector<Vertex>& vertices, float screenW, float screenH) {
        // 1. 上传顶点(交替用双缓冲,避免 GPU 读上一帧时被覆盖)
        vertexFrame = (vertexFrame + 1) % 2;
        auto& vbuf = vertexBuffer[vertexFrame];
        auto& vmem = vertexMemory[vertexFrame];
        if (!vertices.empty()) {
            void* mapped = vmem.mapMemory(0, vertices.size() * sizeof(Vertex));
            std::memcpy(mapped, vertices.data(), vertices.size() * sizeof(Vertex));
            vmem.unmapMemory();
        }

        // 2. 绑定管线 + 描述符 + 顶点
        cmdbuf.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
        cmdbuf.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *pipelineLayout, 0, {*descSet}, {});

        // 3. push constants:正交矩阵(像素→NDC,y 翻转)+ screenW/H + snapPixel
        struct PushConsts {
            float mvp[16];
            float screenW, screenH, snapPixel;
        } pc{};
        // 相机变换:相机对准的世界点 (camX,camY) 显示在屏幕中心,zoom 缩放
        // ndc.x = (wx - camX) * zoom * 2/w   →  (camX, camY) 映射到 NDC (0,0) 即屏幕中心
        // 列主序: 屏幕映射 × 相机(缩放+平移)
        float camX = camera ? camera->x : 0.0f;
        float camY = camera ? camera->y : 0.0f;
        float z = camera ? camera->zoom : 1.0f;
        pc.mvp[0] = 2.0f * z / screenW;  pc.mvp[4] = 0;                pc.mvp[8] = 0;  pc.mvp[12] = -2.0f * z * camX / screenW;
        pc.mvp[1] = 0;                   pc.mvp[5] = 2.0f * z / screenH;  pc.mvp[9] = 0;  pc.mvp[13] = -2.0f * z * camY / screenH;
        pc.mvp[2] = 0;                   pc.mvp[6] = 0;                pc.mvp[10] = 1; pc.mvp[14] = 0;
        pc.mvp[3] = 0;                   pc.mvp[7] = 0;                pc.mvp[11] = 0; pc.mvp[15] = 1;
        pc.screenW = screenW;
        pc.screenH = screenH;
        pc.snapPixel = 0.0f;
        cmdbuf.pushConstants(*pipelineLayout, vk::ShaderStageFlagBits::eVertex, 0, sizeof(pc), &pc);

        // 4. 绘制
        if (!vertices.empty()) {
            cmdbuf.bindVertexBuffers(0, {*vbuf}, {0});
            cmdbuf.draw(static_cast<uint32_t>(vertices.size()), 1, 0, 0);
        }
    }
}
