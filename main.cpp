#include "youklx/iall.hpp"

int main() {
    youklx::init();
    youklx::Window window;
    window.init(1.778);
    window.create();
    
    std::cin.get();
}
