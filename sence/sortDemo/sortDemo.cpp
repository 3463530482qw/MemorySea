#include "vmode.cpp"

extern "C" EXPORT void sortDemo() {
    SDL_Renderer* ren = SDL_CreateRenderer(window.id, NULL);
    int arr[] = {5, 3, 8, 1, 9, 2, 7};
    const int n = 7;
    int cmpA = -1, cmpB = -1;
    int i = 0, j = 0;
    bool done = false;
    Uint64 lastStep = SDL_GetTicks();
    int ww = window.w, wh = window.h;

    while (window.isrun) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) window.isrun = false;
            if (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE) {
                Scene.ptr = "mainMenu";
                SDL_DestroyRenderer(ren);
                return;
            }
        }

        Uint64 now = SDL_GetTicks();
        if (!done && now - lastStep > 200) {
            lastStep = now;
            if (i < n-1) {
                if (j < n) {
                    cmpA = i; cmpB = j; j++;
                } else {
                    int minIdx = i;
                    for (int k = i+1; k < n; k++)
                        if (arr[k] < arr[minIdx]) minIdx = k;
                    int tmp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = tmp;
                    i++; j = i+1;
                }
            } else {
                done = true;
            }
        }

        // 背景
        SDL_SetRenderDrawColor(ren, 20, 20, 32, 255);
        SDL_RenderClear(ren);

        // 绘制水平参考线
        SDL_SetRenderDrawColor(ren, 50, 50, 70, 255);
        for (int y = 100; y < wh-50; y += 50) {
            SDL_FRect line = {50.0f, (float)y, (float)(ww - 100), 1.0f};
            SDL_RenderFillRect(ren, &line);
        }

        // 条形图参数（全部使用 float）
        float barW = (float)(ww - 100) / (float)n - 20.0f;
        float bottom = (float)(wh - 80);
        float x0 = 50.0f;

        for (int k = 0; k < n; k++) {
            float barH = (float)(arr[k] * 40);
            SDL_FRect bar = {x0 + (float)k * (barW + 20.0f), bottom - barH, barW, barH};

            int r, g, b;
            if (k == cmpA || k == cmpB) {
                r = 255; g = 100; b = 100;
            } else if (done) {
                r = 100; g = 255; b = 100;
            } else {
                r = 80; g = 140; b = 255;
            }
            SDL_SetRenderDrawColor(ren, r, g, b, 255);
            SDL_RenderFillRect(ren, &bar);

            // 柱子底部数字标记（色块）
            SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
            SDL_FRect numMark = {bar.x + bar.w * 0.3f, bottom + 5.0f, bar.w * 0.4f, 10.0f};
            SDL_RenderFillRect(ren, &numMark);
        }

        // 顶部标题
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_FRect title = {(float)ww * 0.3f, 20.0f, (float)ww * 0.4f, 20.0f};
        SDL_RenderFillRect(ren, &title);

        // 底部提示（修正点）
        SDL_SetRenderDrawColor(ren, 180, 180, 180, 255);
        SDL_FRect hint = {10.0f, (float)(wh - 30), 200.0f, 15.0f};
        SDL_RenderFillRect(ren, &hint);

        SDL_RenderPresent(ren);
        window.run();
    }
    SDL_DestroyRenderer(ren);
}