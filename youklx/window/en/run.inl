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
                case SDL_EVENT_MOUSE_MOTION:
                    mupdate(pept.motion.x,pept.motion.y);
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    mwupdate(pept.window.data1,pept.window.data2); 
                    break;
                case SDL_EVENT_USER:
                    SDL_SetWindowIcon(id, static_cast<SDL_Surface*>(pept.user.data1));
                    SDL_DestroySurface(static_cast<SDL_Surface*>(pept.user.data1));
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
