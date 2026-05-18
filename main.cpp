#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    window.init(1.778);
    {
        youklx::windowcreateinfo wcreatinfo;
        wcreatinfo.loadini("ini/window/window.ini").load();
        window.create(wcreatinfo);
    }
    
    std::cin.get();
}
