#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    youklx::Sence sence;
    {
        youklx::Image image;
        image.ilpng("ini/main.ini", "icon");
        youklx::windowcreateinfo wc;
        wc.loadini("ini/main.ini","windowcreate").load();
        window.init(1.7778)
        .create(wc)
        .positionAdjustment()
        .icon(image.ima[0][0]);
    }
    sence.ldll("add.dll","add");
    
    while(window.isrun) {
        if (auto it = sence.dict.find("add"); it != sence.dict.end()) {
            it->second();
        } 
    }
}
