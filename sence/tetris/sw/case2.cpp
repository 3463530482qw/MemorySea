// 俄罗斯方块 — 游戏主体

// 方块形状定义 (4x4, 每个形状4个旋转状态)
static const int PIECES[7][4][4][4] = {
    // I
    {
        {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
        {{0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0}},
        {{0,0,0,0}, {0,0,0,0}, {1,1,1,1}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,1,0,0}}
    },
    // O
    {
        {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}}
    },
    // T
    {
        {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0}},
        {{0,0,0,0}, {1,1,1,0}, {0,1,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}
    },
    // S
    {
        {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,1,0}, {0,0,1,0}, {0,0,0,0}},
        {{0,0,0,0}, {0,1,1,0}, {1,1,0,0}, {0,0,0,0}},
        {{1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0}}
    },
    // Z
    {
        {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,0,1,0}, {0,1,1,0}, {0,1,0,0}, {0,0,0,0}},
        {{0,0,0,0}, {1,1,0,0}, {0,1,1,0}, {0,0,0,0}},
        {{0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0}}
    },
    // J
    {
        {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,1,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0}},
        {{0,0,0,0}, {1,1,1,0}, {0,0,1,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0}}
    },
    // L
    {
        {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
        {{0,1,0,0}, {0,1,0,0}, {0,1,1,0}, {0,0,0,0}},
        {{0,0,0,0}, {1,1,1,0}, {1,0,0,0}, {0,0,0,0}},
        {{1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0}}
    }
};

// 颜色 (r,g,b) 用于 draw.line
static const int COLORS[7][3] = {
    {0,   255, 255}, // I - 青色
    {255, 255, 0},   // O - 黄色
    {128, 0,   255}, // T - 紫色
    {0,   255, 0},   // S - 绿色
    {255, 0,   0},   // Z - 红色
    {0,   0,   255}, // J - 蓝色
    {255, 128, 0}    // L - 橙色
};

static const int BW = 10; // 棋盘宽度
static const int BH = 20; // 棋盘高度
static const int CELL = 32; // 单元格像素
static const int previewCell = 24;
static constexpr int OFFX = 640; // 640
static constexpr int OFFY = 130;  // 130
static const int bw = 320, bh = 640;
static const int previewX = 1000;
static const int previewY = 145;

struct Pos { int x, y; };

void splashScreenAnimation2(int &pt) {
    static int board[BH][BW]           = {0};
    static int curPiece                = 0;
    static int curRot                  = 0;
    static int curX                    = 0;
    static int curY                    = 0;
    static int nextPiece               = 0;
    static float dropTimer             = 0.0f;
    static float dropInterval          = 0.8f;
    static int score                   = 0;
    static bool gameOver               = false;
    static bool inited                 = false;

    // 输入锁
    static float inputLockTimer        = 0.0f;
    static const float inputLockDelay  = 0.08f;
    static bool inputLocked            = false;
    static youklx::Linecmd grid{
        .r = {20, 20},
        .g = {20, 20},
        .b = {20, 20},
        .a = {0.15f, 0.15f}
    };
    static youklx::Linecmd bias{
        .thickness = 28,
    };
    static youklx::Linecmd shad{
        .thickness = 28,
        .r = {100,100},
        .g = {100,100},
        .b = {100,100},
        .a = {0.3f,0.3f}
    };
    static youklx::Linecmd curr{
        .thickness = 28,
    };
    static youklx::Linecmd next{
        .thickness = 22,
    };
    // ---- 碰撞检测（两个线程共用） ----
    auto checkCollision = [&](int px, int py, int piece, int rot) -> bool {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[piece][rot][r][c]) {
                    int bx = px + c;
                    int by = py + r;
                    if (bx < 0 || bx >= BW || by >= BH) return true;
                    if (by >= 0 && board[by][bx] != 0) return true;
                }
            }
        }
        return false;
    };

    thread.wth_update([&]() {
    if (!inited) {
        // 初始化棋盘
        for (int r = 0; r < BH; r++)
            for (int c = 0; c < BW; c++)
                board[r][c] = 0;
        std::srand((unsigned int)std::time(nullptr));
        curPiece = std::rand() % 7;
        nextPiece = std::rand() % 7;
        curRot = 0;
        curX = BW / 2 - 2;
        curY = 0;
        score = 0;
        gameOver = false;
        dropTimer = 0.0f;
        dropInterval = 0.8f;
        inputLocked = false;
        inputLockTimer = 0.0f;
        inited = true;
    }

    float dt = window.time.different;
    if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;

    // ---- 放置方块 ----
    auto placePiece = [&]() {
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[curPiece][curRot][r][c]) {
                    int by = curY + r;
                    int bx = curX + c;
                    if (by >= 0 && by < BH && bx >= 0 && bx < BW) {
                        board[by][bx] = curPiece + 1;
                    }
                }
            }
        }
    };

    // ---- 消除行 ----
    auto clearLines = [&]() {
        int cleared = 0;
        for (int r = BH - 1; r >= 0; r--) {
            bool full = true;
            for (int c = 0; c < BW; c++) {
                if (board[r][c] == 0) { full = false; break; }
            }
            if (full) {
                cleared++;
                for (int rr = r; rr > 0; rr--)
                    for (int c = 0; c < BW; c++)
                        board[rr][c] = board[rr - 1][c];
                for (int c = 0; c < BW; c++) board[0][c] = 0;
                r++;
            }
        }
        if (cleared > 0 && cleared <= 4) {
            int scores[] = {0, 100, 300, 500, 800};
            score += scores[cleared];
        }
    };

    // ---- 生成新方块 ----
    auto spawnPiece = [&]() {
        curPiece = nextPiece;
        nextPiece = std::rand() % 7;
        curRot = 0;
        curX = BW / 2 - 2;
        curY = 0;
        if (checkCollision(curX, curY, curPiece, curRot)) {
            gameOver = true;
        }
    };

    // ---- 输入处理 ----
    static bool piecePlacedThisFrame = false;
    piecePlacedThisFrame = false;

    if (!gameOver) {
        // 输入锁更新
        if (inputLocked) {
            inputLockTimer += dt;
            if (inputLockTimer >= inputLockDelay) {
                inputLocked = false;
                inputLockTimer = 0.0f;
            }
        }

        if (!inputLocked) {
            bool acted = false;
            if (window.keyboard.isPressed(SDLK_LEFT)) {
                if (!checkCollision(curX - 1, curY, curPiece, curRot)) {
                    curX--;
                    acted = true;
                }
            }
            if (window.keyboard.isPressed(SDLK_RIGHT)) {
                if (!checkCollision(curX + 1, curY, curPiece, curRot)) {
                    curX++;
                    acted = true;
                }
            }
            if (window.keyboard.isPressed(SDLK_DOWN)) {
                if (!checkCollision(curX, curY + 1, curPiece, curRot)) {
                    curY++;
                    score += 1;
                    acted = true;
                }
            }
            if (window.keyboard.isPressed(SDLK_UP)) {
                int newRot = (curRot + 1) % 4;
                if (!checkCollision(curX, curY, curPiece, newRot)) {
                    curRot = newRot;
                    acted = true;
                }
            }
            if (window.keyboard.isPressed(SDLK_SPACE)) {
                while (!checkCollision(curX, curY + 1, curPiece, curRot)) curY++;
                placePiece();
                clearLines();
                spawnPiece();
                dropTimer = 0.0f;
                acted = true;
                piecePlacedThisFrame = true;
            }
            if (acted) {
                inputLocked = true;
                inputLockTimer = 0.0f;
            }
        }
    }

    // ---- 自动下落 ----
    // 若本帧输入已触发放置+spawn，跳过自动下落防止同一帧重复spawn
    if (!gameOver && !piecePlacedThisFrame) {
        dropTimer += dt;
        if (dropTimer >= dropInterval) {
            dropTimer -= dropInterval;
            if (!checkCollision(curX, curY + 1, curPiece, curRot)) {
                curY++;
            } else {
                placePiece();
                clearLines();
                spawnPiece();
                dropTimer = 0.0f;
            }
        }
    }

    // ESC 返回
    if (window.keyboard.isPressed(SDLK_ESCAPE)) { inited = false; pt = 3; return; }

    // ======== 绘制 ========
    });

    thread.wth_draw([&]() {
    draw.image(youklx::Imagecmd{image.ima[0][0], 0.0f, 0.0f, 1600.0f, 900.0f});

    // ---- 网格线 ----
    for (int r = 0; r <= BH; r++) {
        int y = OFFY + r * CELL;
        grid.sp1(OFFX, y)
            .sp2(OFFX+bw, y);
        draw.line(grid);
    }
    for (int c = 0; c <= BW; c++) {
        int x = OFFX + c * CELL;
        grid.sp1(x, OFFY)
            .sp2(x, OFFY+bh);
        draw.line(grid);
    }

    // ---- 已固定方块 ----
    for (int r = 0; r < BH; r++) {
        for (int c = 0; c < BW; c++) {
            if (board[r][c] != 0) {
                int idx = board[r][c] - 1;
                int bx = OFFX + c * CELL + 2;
                int by = OFFY + r * CELL + 2;
                int midY = by + 14;
                bias.sp1(bx, midY)
                    .sp2(bx + 28, midY)
                    .sr({COLORS[idx][0], COLORS[idx][0]})
                    .sg({COLORS[idx][1], COLORS[idx][1]})
                    .sb({COLORS[idx][2], COLORS[idx][2]});
                draw.line(bias);
            }
        }
    }

    // ---- 阴影（预览下落位置） ----
    if (!gameOver) {
        int ghostY = curY;
        while (!checkCollision(curX, ghostY + 1, curPiece, curRot)) ghostY++;
        if (ghostY != curY) {
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    if (PIECES[curPiece][curRot][r][c]) {
                        int gy = ghostY + r;
                        if (gy >= 0) {
                            int gx = OFFX + (curX + c) * CELL + 2;
                            int gyPos = OFFY + gy * CELL + 2;
                            int midY = gyPos + 14;
                            shad.sp1(gx, midY)
                                .sp2(gx + 28, midY);
                            draw.line(shad);
                        }
                    }
                }
            }
        }
    }

    // ---- 当前方块 ----
    if (!gameOver) {
        int idx = curPiece;
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[curPiece][curRot][r][c]) {
                    int py = curY + r;
                    if (py >= 0) {
                        int px = OFFX + (curX + c) * CELL + 2;
                        int ppx = OFFY + py * CELL + 2;
                        int midY = ppx + 14;
                        curr.sp1(px, midY)
                            .sp2(px + 28, midY)
                            .sr({COLORS[idx][0], COLORS[idx][0]})
                            .sg({COLORS[idx][1], COLORS[idx][1]})
                            .sb({COLORS[idx][2], COLORS[idx][2]});
                        draw.line(curr);
                    }
                }
            }
        }
    }

    // ---- 下一个方块预览 ----
    {
        draw.font(youklx::Fontcmd{&font, "Next",
                  (float)previewX, (float)previewY - 8.0f, 22.0f, 0,0,0,
                  {0.8f, 0.8f, 0.8f, 1.0f}});

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (PIECES[nextPiece][0][r][c]) {
                    int px = previewX + c * previewCell + 1;
                    int py = previewY + r * previewCell + 16;
                    int midY = py + 10;
                    next.sp1(px, midY)
                        .sp2(px + 24, midY)
                        .sr({COLORS[nextPiece][0], COLORS[nextPiece][0]})
                        .sg({COLORS[nextPiece][1], COLORS[nextPiece][1]})
                        .sb({COLORS[nextPiece][2], COLORS[nextPiece][2]});
                    draw.line(next);
                }
            }
        }
    }

    // ---- 分数 ----
    {
        char buf[64];
        std::snprintf(buf, sizeof(buf), "分数 %d", score);
        draw.font(youklx::Fontcmd{&font, buf,
                  (float)(OFFX + bw + 30), (float)(OFFY + 100), 28.0f, 0,0,0,
                  {1.0f, 1.0f, 1.0f, 1.0f}});
    }

    // ---- 操作提示 ----
    draw.font(youklx::Fontcmd{&font, "← → 移动",
              (float)(OFFX + bw + 30), (float)(OFFY + 200), 20.0f, 0,0,0,
              {1.0f, 1.0f, 1.0f, 0.5f}});
    draw.font(youklx::Fontcmd{&font, "↑ 旋转",
              (float)(OFFX + bw + 30), (float)(OFFY + 230), 20.0f, 0,0,0,
              {1.0f, 1.0f, 1.0f, 0.5f}});
    draw.font(youklx::Fontcmd{&font, "↓ 加速",
              (float)(OFFX + bw + 30), (float)(OFFY + 260), 20.0f, 0,0,0,
              {1.0f, 1.0f, 1.0f, 0.5f}});
    draw.font(youklx::Fontcmd{&font, "空格 硬降",
              (float)(OFFX + bw + 30), (float)(OFFY + 290), 20.0f, 0,0,0,
              {1.0f, 1.0f, 1.0f, 0.5f}});
    draw.font(youklx::Fontcmd{&font, "ESC 返回",
              (float)(OFFX + bw + 30), (float)(OFFY + 340), 18.0f, 0,0,0,
              {1.0f, 1.0f, 1.0f, 0.35f}});
    });
    // ---- 游戏结束遮罩 ----
    if (gameOver) {
        draw.image(youklx::Imagecmd{image.ima[0][0], static_cast<float>(OFFX), static_cast<float>(OFFY), static_cast<float>(bw), static_cast<float>(bh), 0.0f, 0.0f, 0.0f,
                  {0,0,0,0.6f}, {0,0,0,0.6f}, {0,0,0,0.6f}, {0,0,0,0.6f}});
        draw.font(youklx::Fontcmd{&font, "游戏结束",
                  (float)(OFFX + bw/2 - 85), (float)(OFFY + bh/2 - 40), 48.0f, 0,0,0,
                  {1.0f, 0.3f, 0.3f, 1.0f}});
        char buf[64];
        std::snprintf(buf, sizeof(buf), "得分 %d", score);
        draw.font(youklx::Fontcmd{&font, buf,
                  (float)(OFFX + bw/2 - 50), (float)(OFFY + bh/2 + 30), 32.0f, 0,0,0,
                  {1.0f, 1.0f, 1.0f, 0.9f}});
        draw.font(youklx::Fontcmd{&font, "ESC 返回",
                  (float)(OFFX + bw/2 - 50), (float)(OFFY + bh/2 + 80), 24.0f, 0,0,0,
                  {1.0f, 1.0f, 1.0f, 0.7f}});
    }
}