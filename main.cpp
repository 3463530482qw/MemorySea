#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    {
        youklx::windowcreateinfo wc;
        wc.loadini("ini/window/window.ini").load();
        window.init(1.778)
        .create(wc)
        .positionAdjustment();
    }
    while(window.isrun) {
        window.run();
    }
    
}
