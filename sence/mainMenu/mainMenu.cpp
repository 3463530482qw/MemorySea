#include "vmode.cpp"

// 创建圆角矩形纹理（带阴影，纯软件绘制，无 cos/sin）
static SDL_Texture* CreateRoundedButton(SDL_Renderer* ren, int w, int h, int radius,
                                        int r1, int g1, int b1,   // 主色
                                        int r2, int g2, int b2) { // 阴影色
    SDL_Texture* tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
                                          SDL_TEXTUREACCESS_TARGET, w, h);
    if (!tex) return nullptr;
    SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

    SDL_Texture* oldTarget = SDL_GetRenderTarget(ren);
    SDL_SetRenderTarget(ren, tex);

    // 清空为透明
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderClear(ren);

    // 1. 柔和阴影（多层偏移半透明矩形）
    for (int i = 0; i < 3; ++i) {
        int offset = i + 2;
        SDL_SetRenderDrawColor(ren, r2, g2, b2, 30 - i * 8);
        SDL_FRect s = { (float)offset, (float)offset, (float)(w - offset * 2), (float)(h - offset * 2) };
        SDL_RenderFillRect(ren, &s);
    }

    // 2. 主体（中心矩形 + 四条边 + 角部像素填充）
    SDL_SetRenderDrawColor(ren, r1, g1, b1, 255);

    // 中间横条（去掉左右圆角区）
    SDL_FRect center = { (float)radius, 0.0f, (float)(w - radius * 2), (float)h };
    SDL_RenderFillRect(ren, &center);
    // 中间竖条（去掉上下圆角区）
    SDL_FRect middle = { 0.0f, (float)radius, (float)w, (float)(h - radius * 2) };
    SDL_RenderFillRect(ren, &middle);

    // 填充四个圆角（用细横条逐行填充，模拟圆角）
    for (int y = 0; y < radius; ++y) {
        // 根据圆方程计算当前行对应的宽度偏移
        float dy = (float)(radius - y);
        float offset = radius - sqrtf(radius * radius - dy * dy);
        int leftWidth = (int)(radius - offset);
        if (leftWidth < 0) leftWidth = 0;

        // 左上角
        SDL_FRect lu = { 0.0f, (float)y, (float)leftWidth, 1.0f };
        SDL_RenderFillRect(ren, &lu);
        // 右上角
        SDL_FRect ru = { (float)(w - leftWidth), (float)y, (float)leftWidth, 1.0f };
        SDL_RenderFillRect(ren, &ru);
        // 左下角
        SDL_FRect lb = { 0.0f, (float)(h - y - 1), (float)leftWidth, 1.0f };
        SDL_RenderFillRect(ren, &lb);
        // 右下角
        SDL_FRect rb = { (float)(w - leftWidth), (float)(h - y - 1), (float)leftWidth, 1.0f };
        SDL_RenderFillRect(ren, &rb);
    }

    SDL_SetRenderTarget(ren, oldTarget);
    return tex;
}

extern "C" EXPORT void mainMenu() {

    while (window.isrun) {
        window.run();
        vulkan.drawFrame();
    }

}