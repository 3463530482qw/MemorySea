namespace youklx {
    Window& Window::run() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                isrun = false;
            }
        }
        return *this;
    }
}
