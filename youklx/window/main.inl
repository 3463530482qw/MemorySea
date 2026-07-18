namespace youklx {
    Window::Window() {
        int count = 0;
        SDL_DisplayID* ids = SDL_GetDisplays(&count);
        displays.assign(ids, ids + count);
        SDL_free(ids);
    }
    Window::~Window() {
        if (id) {
            SDL_DestroyWindow(id);
            id = nullptr;
        }
    }
}