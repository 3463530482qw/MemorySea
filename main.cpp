#include "youklx/iall.hpp"

int main() {

    youklx::Window window;
    youklx::Window& win = window;
    {
        youklx::windowcreateinfo creatinfo{};
        win.create(
            creatinfo
            .name("MemorySea")
            .w(199)
            .h(199)
            .noresize(true)
            .allowdnd(true)
            .center(true)
        );
    }
    
    
    std::cin.get();
}
