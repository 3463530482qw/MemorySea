namespace youklx {
    Window::~Window() {
        if (id) {
            SDL_DestroyWindow(id);
            id = nullptr;
        }
    }
}