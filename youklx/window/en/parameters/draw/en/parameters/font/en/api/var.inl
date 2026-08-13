Font* fot{nullptr};             // 字体对象指针
std::string text;               // 要绘制的文字
float x{0.0f}, y{0.0f};         // 绘制位置（左上角）
float fontSize{20.0f};          // 文字大小
float rotate{0.0f};             // 旋转角度
float rox{0.0f}, roy{0.0f};     // 旋转中心偏移
std::array<float, 4> rgba{1.0f, 1.0f, 1.0f, 1.0f};
mutable std::vector<Vertex> vertices;   // 顶点缓冲(设置函数标脏后,由绘制时重新计算填充)
mutable bool dirty{true};               // 脏标记(参数变化置脏,未调用设置函数则不重算)
