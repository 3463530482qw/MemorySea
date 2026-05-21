#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    {
        youklx::Image image;
        image.ilpng("ini/main.ini", "icon");
        youklx::windowcreateinfo wc;
        wc.loadini("ini/main.ini","windowcreate").load();
        window.init(1.778)
        .create(wc)
        .positionAdjustment()
        .icon(image.ima[0][0]);
    }
    while(window.isrun) {
        window.run();
    }
}
