std::vector<Vertex> vertices;   // 所有绘制的通用顶点数据(vulkan 可直接上传,按绘制顺序排列)
std::vector<Batch> batches;     // 顶点字体批次(与 vertices 同序,渲染端据此切换图集)
std::mutex vertMtx;             // 顶点缓冲互斥(更新线程并发 push 时保护)
