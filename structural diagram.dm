graph TD
    %% ===== 第三方依赖层 =====
    A[libc / C++ STL] --> B[youklx/iall.hpp 全局类型与导入导出]
    C[SDL3 媒体库] --> D[youklx/window 窗口与输入]
    C --> E[youklx/vulkan 渲染器]
    F[Vulkan SDK] --> E
    G[inih INI解析] --> B
    H[stb_image] --> I[youklx/image 图片加载与图集]
    J[stb_truetype] --> K[youklx/font 字体加载与字形]
    L[spine-4.3 骨骼动画] --> B

    %% ===== 引擎核心模块 =====
    B --> D
    B --> E
    B --> I
    B --> K
    B --> M[youklx/draw 绘制命令与顶点生成]
    B --> N[youklx/scene 动态场景 DLL 加载]
    B --> O[youklx/thread 更新与绘制线程调度]

    %% ===== 着色器与渲染 =====
    P[shaders/line + image + font] --> E

    %% ===== 应用入口 =====
    Q[main.cpp 入口] --> R[vmain.cpp 导出全局对象]
    Q --> I
    Q --> D
    Q --> E
    Q --> K
    Q --> N
    Q --> O
    Q --> M

    %% ===== 全局共享对象 =====
    R --> B
    R --> D
    R --> E
    R --> I
    R --> K
    R --> M
    R --> N
    R --> O

    %% ===== 场景 DLL 访问 =====
    R -.->|DLL import| S[vmode.cpp 引入全局对象]
    N -->|scene.ldlli ini/scene/main.ini scene| T[Scene 字典加载]
    T -->|LoadLibrary + GetProcAddress| U[场景 DLL 激活函数]

    U --> V[sence/mainMenu 主菜单]
    U --> W[sence/mselect 游戏选择]
    U --> X[sence/tetris 俄罗斯方块]
    U --> Y[sence/snake 贪吃蛇]
    U --> Z[sence/sudoku 数独]
    U --> AA[sence/jump 平台跳跃]

    %% ===== 主循环 =====
    Q --> AB[while window.isrun]
    AB -->|scene.ptr| T
    AB -->|调用 scene.dict| U

    %% ===== 场景跳转 =====
    V -->|开始| W
    W -->|选择| X
    W -->|选择| Y
    W -->|选择| Z
    W -->|选择| AA
    X -->|ESC/返回| W
    Y -->|ESC/返回| W
    Z -->|ESC/返回| W
    AA -->|ESC/返回| W
    V -->|结束| AC[退出程序]

    %% ===== 运行时数据流 =====
    D -.->|事件输入| O
    O -->|wth_update| AD[更新线程]
    O -->|wth_draw| AE[绘制线程]
    AD -->|update + vertex生成| M
    AD -->|纹理更新| E
    AD -->|顶点缓冲更新| E
    AD -->|渲染帧| E
    AE -->|绘制命令记录| M
    M -->|顶点缓冲| E
    E -->|viewport frame| D

    %% ===== 关键交互依赖 =====
    I -->|mouse/keyboard| V
    I -->|viewport映射| E
    M -->|Linecmd / Imagecmd / Fontcmd| E
    K -->|字体纹理| E
    I -->|窗口大小| E
