namespace youklx {
    Window& Window::run() {
        time.update();
        key.update();
        while (SDL_PollEvent(&pept)) {
            if (pept.window.windowID != 0 && pept.window.windowID != wid) {
                pe.push_back(pept);
                continue;
            }
            switch (pept.type) {
                case SDL_EVENT_QUIT:
                    isrun = false;
                    break;
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    isrun = false;
                    break;
                default:
                    break;
            }
        }
        for (auto& e : pe) {  
            SDL_PushEvent(&e);
        }
        pe.clear();
        return *this;
    }
}
