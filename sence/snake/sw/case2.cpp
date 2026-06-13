void splashScreenAnimation2(int &pt) {
    // 贪吃蛇 — 游戏主体
    static constexpr int COLS = 30;
    static constexpr int ROWS = 22;
    static constexpr int CELL = 30;
    static constexpr int OFFX = 350;
    static constexpr int OFFY = 120;

    struct Pos { int x, y; };

    static std::vector<Pos> snake;
    static int dirX = 1, dirY = 0;
    static int nextDirX = 1, nextDirY = 0;
    static Pos food{};
    static float moveTimer = 0.0f;
    static float moveInterval = 0.12f;
    static int score = 0;
    static bool dead = false;
    static bool inited = false;
    static youklx::Linecmd grid{
        .r = {30, 30},
        .g = {30, 30},
        .b = {30, 30},
        .a = {0.3f, 0.3f}
    };
    static youklx::Linecmd dfood{
        .g = {30, 30},
        .b = {30, 30},
    };
    static youklx::Linecmd snk{
        .r = {0, 0},
        .b = {50, 50},
    };
    thread.wth_update([&]() {
    if (!inited) {
        snake.clear();
        snake.push_back({COLS / 2, ROWS / 2});
        snake.push_back({COLS / 2 - 1, ROWS / 2});
        snake.push_back({COLS / 2 - 2, ROWS / 2});
        dirX = 1; dirY = 0;
        nextDirX = 1; nextDirY = 0;
        score = 0;
        dead = false;
        moveTimer = 0.0f;
        moveInterval = 0.12f;
        // 随机食物
        food.x = std::rand() % COLS;
        food.y = std::rand() % ROWS;
        inited = true;
    }

    float dt = window.time.different;
    if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;

    // 输入
    if (!dead) {
        if (window.keyboard.isPressed(SDLK_LEFT)  && dirX == 0) { nextDirX = -1; nextDirY = 0; }
        if (window.keyboard.isPressed(SDLK_RIGHT) && dirX == 0) { nextDirX = 1;  nextDirY = 0; }
        if (window.keyboard.isPressed(SDLK_UP)    && dirY == 0) { nextDirX = 0;  nextDirY = -1; }
        if (window.keyboard.isPressed(SDLK_DOWN)  && dirY == 0) { nextDirX = 0;  nextDirY = 1; }

        moveTimer += dt;
        if (moveTimer >= moveInterval) {
            moveTimer -= moveInterval;
            dirX = nextDirX; dirY = nextDirY;

            Pos head = snake[0];
            head.x += dirX; head.y += dirY;

            // 碰壁 -> 死
            if (head.x < 0 || head.x >= COLS || head.y < 0 || head.y >= ROWS) {
                dead = true;
            }
            // 碰自己 -> 死
            for (size_t i = 0; i < snake.size(); i++) {
                if (snake[i].x == head.x && snake[i].y == head.y) {
                    dead = true; break;
                }
            }

            if (!dead) {
                snake.insert(snake.begin(), head);
                if (head.x == food.x && head.y == food.y) {
                    score += 10;
                    food.x = std::rand() % COLS;
                    food.y = std::rand() % ROWS;
                    if (moveInterval > 0.05f) moveInterval -= 0.003f;
                } else {
                    snake.pop_back();
                }
            }
        }
    }

    if (window.keyboard.isPressed(SDLK_ESCAPE)) { inited = false; pt = 3; return; }
    });

    thread.wth_draw([&]() {
    // ---- 绘制 ----
    draw.image(youklx::Imagecmd{image.ima[0][0], 0, 0, 1600, 900});

    int bw = COLS * CELL, bh = ROWS * CELL;

    // 网格线
    for (int r = 0; r <= ROWS; r++) {
        int y = OFFY + r * CELL;
        grid.sp1(OFFX, y).sp2(OFFX+bw, y);
        draw.line(grid);
    }
    for (int c = 0; c <= COLS; c++) {
        int x = OFFX + c * CELL;
        grid.sp1(x, OFFY).sp2(x, OFFY+bh);
        draw.line(grid);
    }

    // 食物 (红色方块)
    {
        int fx = OFFX + food.x * CELL + 3;
        int fy = OFFY + food.y * CELL;
        int fcx = fx + CELL / 2;
        int fcy = fy + CELL / 2;
        dfood.sp1(fx, fcy)
             .sp2(fx + CELL - 6, fcy)
             .slw((float)(CELL - 6));
        draw.line(dfood);
    }

    // 蛇身 (绿色方块)
    for (size_t i = 0; i < snake.size(); i++) {
        int sx = OFFX + snake[i].x * CELL + 2;
        int sy = OFFY + snake[i].y * CELL + 2;
        int midY = sy + (CELL-4)/2;
        int bright = (i == 0) ? 255 : 180;
        snk.sp1(sx, midY)
           .sp2(sx + CELL - 4, midY)
           .slw((float)(CELL - 4))
           .sg({bright,bright});
        draw.line(snk);
    }

    // UI
    char buf[64];
    std::snprintf(buf, sizeof(buf), "分数 %d", score);
    draw.font(youklx::Fontcmd{&font, buf, 60, 50, 52.0f, 0,0,0, {1.0f,1.0f,1.0f,1.0f}});

    draw.font(youklx::Fontcmd{&font, "← → ↑ ↓ 方向",
              60, 740.0f, 26.0f, 0,0,0, {1.0f,1.0f,1.0f,0.6f}});
    draw.font(youklx::Fontcmd{&font, "ESC 返回",
              60, 780.0f, 24.0f, 0,0,0, {1.0f,1.0f,1.0f,0.4f}});

    if (dead) {
        draw.image(youklx::Imagecmd{image.ima[0][0], static_cast<float>(OFFX), static_cast<float>(OFFY), static_cast<float>(bw), static_cast<float>(bh), 0.0f, 0.0f, 0.0f,
                  {0,0,0,0.6f}, {0,0,0,0.6f}, {0,0,0,0.6f}, {0,0,0,0.6f}});
        draw.font(youklx::Fontcmd{&font, "游戏结束",
                  OFFX + 300.0f, OFFY + 250.0f, 56.0f, 0,0,0,
                  {1.0f,0.3f,0.3f,1.0f}});
        std::snprintf(buf, sizeof(buf), "得分 %d", score);
        draw.font(youklx::Fontcmd{&font, buf,
                  OFFX + 310.0f, OFFY + 330.0f, 40.0f, 0,0,0,
                  {1.0f,1.0f,1.0f,0.9f}});
        draw.font(youklx::Fontcmd{&font, "ESC 返回",
                  OFFX + 330.0f, OFFY + 400.0f, 32.0f, 0,0,0,
                  {1.0f,1.0f,1.0f,0.8f}});
    }
    });
}