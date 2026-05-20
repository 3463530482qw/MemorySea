#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    youklx::Image image;
    {
        youklx::Image image;
        image.lpng("image/icon/icon.png");
        youklx::windowcreateinfo wc;
        wc.loadini("ini/window/window.ini").load();
        window.init(1.778)
        .create(wc)
        .positionAdjustment()
        .icon(image.ima[0][0]);
    }
    while(window.isrun) {
        window.run();
    }
    
}
