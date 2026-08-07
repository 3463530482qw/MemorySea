std::vector<Vertex> vertices;   // 所有绘制的通用顶点数据(vulkan 可直接上传)
std::mutex vertMtx;             // 顶点缓冲互斥(更新线程并发 push 时保护)
