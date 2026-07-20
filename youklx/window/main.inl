namespace youklx {
    Window::~Window() {
        run(); 
        if (id) {
            SDL_DestroyWindow(id);
            id = nullptr;
        }
    }
}