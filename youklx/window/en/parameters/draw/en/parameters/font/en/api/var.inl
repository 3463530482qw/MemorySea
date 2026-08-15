Font* fot{nullptr};             // 字体对象指针
std::string text;               // 要绘制的文字
float x{0.0f}, y{0.0f};         // 绘制位置（左上角）
float fontSize{20.0f};          // 文字大小
float rotate{0.0f};             // 旋转角度
float rox{0.0f}, roy{0.0f};     // 旋转中心偏移
std::array<float, 4> rgba{1.0f, 1.0f, 1.0f, 1.0f};
// --- 描边(SDF 片元内绘制) ---
bool outline{false};                                      // 描边开关(关闭时 ow=0,不生成额外顶点)
float outlineW{0.0f};                                     // 描边宽度(em,相对 fontSize,须 ≤ 所绑字体的 pad)
std::array<float, 4> outlineColor{0.0f, 0.0f, 0.0f, 1.0f};// 描边颜色
mutable std::vector<Vertex> vertices;   // 顶点缓冲(设置函数标脏后,由绘制时重新计算填充)
mutable bool dirty{true};               // 脏标记(参数变化置脏,未调用设置函数则不重算)
int order;                              // 绘制顺序(构造时领号,顶点流按此顺序写入)
