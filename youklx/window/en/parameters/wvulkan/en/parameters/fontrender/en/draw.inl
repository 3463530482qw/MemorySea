namespace youklx {
    // 录制前准备:构建渲染段、惰性初始化贴图、上传图集与顶点
    // (上传内部会提交命令并等待,必须在命令缓冲录制之外执行)
    void FontRender::prepare(
        const std::vector<Batch>& batches, 
        const std::vector<Vertex>& vertices,
        float screenW, float screenH
    ) {
        segments.clear();
        if (vertices.empty()) return;

        // 顶点全部来自字体命令(带批次);无批次的裸顶点没有图集可绑,直接跳过不绘制
        segments.reserve(batches.size());
        for (const Batch& b : batches) segments.push_back(b);

        // 段内的字体贴图惰性初始化 + 图集上传(此处仍处于录制外)
        for (const Batch& seg : segments) {
            if (!seg.font) continue;
            if (!seg.font->rendererBound())
                seg.font->bindRenderer(*physicalDevice, *device, descLayout, descPool, sampler, graphicsFamilyIndex);
            seg.font->uploadAtlas();
        }

        // 上传顶点(双缓冲交替,整帧一次映射拷贝)
        vertexFrame = (vertexFrame + 1) % 2;
        vk::raii::Buffer& vbuf = vertexBuffer[vertexFrame];
        vk::raii::DeviceMemory& vmem = vertexMemory[vertexFrame];
        void* mapped = vmem.mapMemory(0, vertices.size() * sizeof(Vertex));
        std::memcpy(mapped, vertices.data(), vertices.size() * sizeof(Vertex));
        vmem.unmapMemory();

        // push constants:正交矩阵(像素→NDC,y 翻转)+ screenW/H + snapPixel
        // 相机变换:相机对准的世界点 (camX,camY) 显示在屏幕中心,zoom 缩放
        // ndc.x = (wx - camX) * zoom * 2/w   →  (camX, camY) 映射到 NDC (0,0) 即屏幕中心
        // 列主序: 屏幕映射 × 相机(缩放+平移)
        pc = {};
        float camX = camera ? camera->x : 0.0f;
        float camY = camera ? camera->y : 0.0f;
        float z = camera ? camera->zoom : 1.0f;
        pc.mvp[0] = 2.0f * z / screenW;  pc.mvp[4] = 0;                  pc.mvp[8] = 0;  pc.mvp[12] = -2.0f * z * camX / screenW;
        pc.mvp[1] = 0;                   pc.mvp[5] = 2.0f * z / screenH;  pc.mvp[9] = 0;  pc.mvp[13] = -2.0f * z * camY / screenH;
        pc.mvp[2] = 0;                   pc.mvp[6] = 0;                  pc.mvp[10] = 1; pc.mvp[14] = 0;
        pc.mvp[3] = 0;                   pc.mvp[7] = 0;                  pc.mvp[11] = 0; pc.mvp[15] = 1;
        pc.screenW = screenW;
        pc.screenH = screenH;
        pc.snapPixel = 0.0f;
    }

    // 纯录制:按 prepare 构建的段绑定图集描述符并绘制
    void FontRender::draw(vk::raii::CommandBuffer& cmdbuf) {
        if (segments.empty()) return;

        vk::raii::Buffer& vbuf = vertexBuffer[vertexFrame];
        cmdbuf.bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline);
        cmdbuf.pushConstants(*pipelineLayout, vk::ShaderStageFlagBits::eVertex, 0, sizeof(pc), &pc);

        // 逐段绑定图集描述符并绘制(段间顶点缓冲偏移累加,避免同帧覆盖)
        size_t vboOffset = 0;
        for (const Batch& seg : segments) {
            if (!seg.font) continue;
            cmdbuf.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, *pipelineLayout, 0, {seg.font->descriptorSet()}, {});
            cmdbuf.bindVertexBuffers(0, {*vbuf}, {vboOffset});
            cmdbuf.draw(static_cast<uint32_t>(seg.count), 1, 0, 0);
            vboOffset += seg.count * sizeof(Vertex);
        }
    }
}
