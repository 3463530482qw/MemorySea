namespace youklx {
    Draw& Draw::font(const Fontcmd& cmd) {
        if (!cmd.fot) return *this;

        // 命令脏才重算顶点缓冲(写命令自己的缓冲;未调用设置函数则沿用,不更新顶点内容)
        if (cmd.dirty) {
            cmd.vertices.clear();
            // 缩放比例 = 目标字号 / 烘焙字号(位图按烘焙字号烤制,绘制时按比例缩放)
            float scale = cmd.fontSize / cmd.fot->size;

            // 收集单字符矩形,逐个发射
            std::vector<fontblock> blocks;
            fontblocks(cmd, scale, blocks);

            float cosr = std::cos(cmd.rotate), sinr = std::sin(cmd.rotate);
            for (const fontblock& b : blocks) fontemit(cmd, b, cosr, sinr);

            cmd.dirty = false;
        }
        if (cmd.vertices.empty()) return *this;

        std::lock_guard lock(vertMtx);   // 并发 push 保护

        // 按绘制顺序定位插入点(批次数少,线性扫描):并行计算的结果在此统一按序写入
        size_t pos = vertices.size();      // 默认尾插
        size_t bidx = batches.size();
        for (size_t i = 0; i < batches.size(); i++) {
            if (batches[i].order > cmd.order) { pos = batches[i].offset; bidx = i; break; }
        }
        size_t added = cmd.vertices.size();
        vertices.insert(vertices.begin() + static_cast<ptrdiff_t>(pos), cmd.vertices.begin(), cmd.vertices.end());
        // 插入点之后的段偏移整体后移
        for (size_t i = bidx; i < batches.size(); i++) batches[i].offset += added;
        // 段合并:仅与相邻的同命令段(同 order 即同一命令)合并
        if (bidx > 0 && batches[bidx-1].order == cmd.order && batches[bidx-1].font == cmd.fot) {
            batches[bidx-1].count += added;
        } else if (bidx < batches.size() && batches[bidx].order == cmd.order && batches[bidx].font == cmd.fot) {
            batches[bidx].offset -= added;
            batches[bidx].count += added;
        } else {
            batches.insert(batches.begin() + static_cast<ptrdiff_t>(bidx), {cmd.fot, pos, added, cmd.order});
        }
        return *this;
    }
}
