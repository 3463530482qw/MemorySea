namespace youklx {
    Window& Window::run() {
        while (SDL_PollEvent(&pe)) {
            switch (pe.type) {
                case SDL_EVENT_QUIT:
                    isrun = false;
                    break;
                default:
                    break;
            }
        }
        return *this;
    }
}