void splashScreenAnimation2(int &pt) {
    // 数独 — 游戏主体
    static constexpr int N = 9;
    static constexpr int CELL = 72;
    static constexpr int OFFX = 476;
    static constexpr int OFFY = 126;
    static youklx::Linecmd grid;

    // 预设谜题 (0 = 空格)
    static int puzzle[N][N] = {
        {5,3,0, 0,7,0, 0,0,0},
        {6,0,0, 1,9,5, 0,0,0},
        {0,9,8, 0,0,0, 0,6,0},

        {8,0,0, 0,6,0, 0,0,3},
        {4,0,0, 8,0,3, 0,0,1},
        {7,0,0, 0,2,0, 0,0,6},

        {0,6,0, 0,0,0, 2,8,0},
        {0,0,0, 4,1,9, 0,0,5},
        {0,0,0, 0,8,0, 0,7,9},
    };

    static int board[N][N];
    static bool fixed[N][N];  // 预设格子不可改
    static int selR = -1, selC = -1;
    static bool inited = false;
    static bool solved = false;

    if (!inited) {
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++) {
                board[r][c] = puzzle[r][c];
                fixed[r][c] = (puzzle[r][c] != 0);
            }
        selR = -1; selC = -1;
        solved = false;
        // 模板命令初始样式（仅首次）
        grid.color(180, 180, 180);
        inited = true;
    }
    // ---- 合法性检测：行/列/宫格是否无重复（两个线程共用） ----
    static bool conflict[N][N]{};
    const int bw = N * CELL, bh = N * CELL;

    thread.wth_update([&]() {
    float dt = window.time.different;
    if (dt > 0.5f || dt <= 0.0f) dt = 0.016f;

    // ---- 鼠标选择 ----
    if (!solved && window.mouse.leftPressed()) {
        int mx = window.mouse.x;
        int my = window.mouse.y;
        if (mx >= OFFX && mx < OFFX + N * CELL && my >= OFFY && my < OFFY + N * CELL) {
            int c = (mx - OFFX) / CELL;
            int r = (my - OFFY) / CELL;
            if (!fixed[r][c]) {
                selR = r; selC = c;
            }
        }
    }

    // ---- 键盘输入 ----
    if (!solved && selR >= 0) {
        for (int k = 1; k <= 9; k++) {
            if (window.keyboard.isPressed((SDL_Keycode)(SDLK_1 + k - 1))) {
                board[selR][selC] = k;
            }
        }
        if (window.keyboard.isPressed(SDLK_0) || window.keyboard.isPressed(SDLK_BACKSPACE) ||
            window.keyboard.isPressed(SDLK_DELETE)) {
            board[selR][selC] = 0;
        }
    }

    if (window.keyboard.isPressed(SDLK_ESCAPE)) { inited = false; pt = 3; return; }

    auto validate = [&]() -> bool {
        bool ok = true;
        for (int r = 0; r < N; r++)
            for (int c = 0; c < N; c++)
                conflict[r][c] = false;

        // 行
        for (int r = 0; r < N; r++) {
            int seen[10] = {};
            for (int c = 0; c < N; c++) {
                int v = board[r][c];
                if (v > 0 && seen[v]) { conflict[r][c] = true; ok = false; }
                seen[v] = 1;
            }
        }
        // 列
        for (int c = 0; c < N; c++) {
            int seen[10] = {};
            for (int r = 0; r < N; r++) {
                int v = board[r][c];
                if (v > 0 && seen[v]) { conflict[r][c] = true; ok = false; }
                seen[v] = 1;
            }
        }
        // 3×3 宫格
        for (int br = 0; br < N; br += 3) {
            for (int bc = 0; bc < N; bc += 3) {
                int seen[10] = {};
                for (int r = br; r < br + 3; r++) {
                    for (int c = bc; c < bc + 3; c++) {
                        int v = board[r][c];
                        if (v > 0 && seen[v]) { conflict[r][c] = true; ok = false; }
                        seen[v] = 1;
                    }
                }
            }
        }
        return ok;
    };

    // ---- 完成检测 ----
    if (!solved) {
        bool full = true;
        for (int r = 0; r < N && full; r++)
            for (int c = 0; c < N && full; c++)
                if (board[r][c] == 0) full = false;
        if (full) {
            if (validate()) {
                solved = true;
            }
        } else {
            validate(); // 实时检测冲突
        }
    }

    // ---- 绘制 ----
    });

    thread.wth_draw([&]() {
    draw.image(youklx::Imagecmd{image.ima[0][0], 0.0f, 0.0f, 1600.0f, 900.0f});

    int bw = N * CELL, bh = N * CELL;

    // 网格线
    for (int r = 0; r <= N; r++) {
        int y = OFFY + r * CELL;
        int thick = (r % 3 == 0) ? 3 : 1;
        grid.from(OFFX, y)
            .to(OFFX+bw, y)
            .slw((float)thick);
        draw.line(grid);
    }
    for (int c = 0; c <= N; c++) {
        int x = OFFX + c * CELL;
        int thick = (c % 3 == 0) ? 3 : 1;
        grid.from(x, OFFY)
            .to(x, OFFY+bh)
            .slw((float)thick);
        draw.line(grid);
    }

    // 选中格子高亮
    if (selR >= 0 && selC >= 0) {
        int sx = OFFX + selC * CELL;
        int sy = OFFY + selR * CELL;
        draw.image(youklx::Imagecmd{image.ima[0][7], (float)sx, (float)sy, (float)CELL, (float)CELL, 0.0f, 0.0f, 0.0f,
                  {55.0f,55.0f,55.0f,0.1f}, {55.0f,55.0f,55.0f,0.1f},
                  {55.0f,55.0f,55.0f,0.1f}, {55.0f,55.0f,55.0f,0.1f}});
    }

    // 数字
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (board[r][c] == 0) continue;
            std::string num = std::to_string(board[r][c]);
            float nx = (float)(OFFX + c * CELL + 22);
            float ny = (float)(OFFY + r * CELL + 23);

            if (fixed[r][c]) {
                draw.font(youklx::Fontcmd{&font, num}.sp(nx, ny).ss(48.0f).srgba({1.0f,1.0f,1.0f,1.0f}));
            } else if (conflict[r][c]) {
                // 冲突：红色
                draw.font(youklx::Fontcmd{&font, num}.sp(nx, ny).ss(48.0f).srgba({1.0f,0.2f,0.2f,1.0f}));
            } else {
                // 正常：青色
                draw.font(youklx::Fontcmd{&font, num}.sp(nx, ny).ss(48.0f).srgba({0.3f,0.8f,1.0f,1.0f}));
            }
        }
    }

    // UI
    draw.font(youklx::Fontcmd{&font, "数独"}.sp(50, 45).ss(48.0f).srgba({0.4f,0.6f,1.0f,1.0f}));
    draw.font(youklx::Fontcmd{&font, "点击格子选中 | 1-9填入 | 0/Backspace清除"}.sp(50, 805.0f).ss(24.0f).srgba({1.0f,1.0f,1.0f,0.5f}));
    });

    if (solved) {
        draw.image(youklx::Imagecmd{image.ima[0][0], static_cast<float>(OFFX), static_cast<float>(OFFY), static_cast<float>(bw), static_cast<float>(bh), 0.0f, 0.0f, 0.0f,
                  {0,0,0,0.6f}, {0,0,0,0.6f}, {0,0,0,0.6f}, {0,0,0,0.6f}});
        draw.font(youklx::Fontcmd{&font, "完成!"}.sp(OFFX + 240.0f, OFFY + 285.0f).ss(72.0f).srgba({0.2f,1.0f,0.3f,1.0f}));
        draw.font(youklx::Fontcmd{&font, "ESC 返回"}.sp(OFFX + 250.0f, OFFY + 375.0f).ss(36.0f).srgba({1.0f,1.0f,1.0f,0.8f}));
    }
}