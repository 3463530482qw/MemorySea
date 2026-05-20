#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    youklx::Image image;
    {
        image.lpng("image/icon/icon.png");
        youklx::windowcreateinfo wc;
        wc.loadini("ini/window/window.ini").load();
        window.init(1.778)
        .create(wc)
        .positionAdjustment();
        auto& png = std::get<youklx::Plpng>(image.ima[0][0]);
        SDL_Surface* surf = SDL_CreateSurfaceFrom(png.w, png.h, SDL_PIXELFORMAT_RGBA32, png.data, png.w * 4);
        SDL_SetWindowIcon(window.id, surf);
    }
    while(window.isrun) {
        window.run();
    }
    
}
