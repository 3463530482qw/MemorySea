namespace youklx {
    void windowscreateinfo::load() {
        flage = static_cast<SDL_WindowFlags>(0);

        if (fullscreen)          flage |= SDL_WINDOW_FULLSCREEN;
        if (render.opengl)       flage |= SDL_WINDOW_OPENGL;
        if (occluded)            flage |= SDL_WINDOW_OCCLUDED;
        if (hidden)              flage |= SDL_WINDOW_HIDDEN;
        if (borderless)          flage |= SDL_WINDOW_BORDERLESS;
        if (resizable)           flage |= SDL_WINDOW_RESIZABLE;
        if (minimized)           flage |= SDL_WINDOW_MINIMIZED;
        if (maximized)           flage |= SDL_WINDOW_MAXIMIZED;
        if (mouse_grabbed)       flage |= SDL_WINDOW_MOUSE_GRABBED;
        if (input_focus)         flage |= SDL_WINDOW_INPUT_FOCUS;
        if (mouse_focus)         flage |= SDL_WINDOW_MOUSE_FOCUS;
        if (external)            flage |= SDL_WINDOW_EXTERNAL;
        if (modal)               flage |= SDL_WINDOW_MODAL;
        if (high_pixel_density)  flage |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
        if (mouse_capture)       flage |= SDL_WINDOW_MOUSE_CAPTURE;
        if (mouse_relative_mode) flage |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
        if (always_on_top)       flage |= SDL_WINDOW_ALWAYS_ON_TOP;
        if (utility)             flage |= SDL_WINDOW_UTILITY;
        if (tooltip)             flage |= SDL_WINDOW_TOOLTIP;
        if (popup_menu)          flage |= SDL_WINDOW_POPUP_MENU;
        if (keyboard_grabbed)    flage |= SDL_WINDOW_KEYBOARD_GRABBED;
        if (fill_document)       flage |= SDL_WINDOW_FILL_DOCUMENT;
        if (render.vulkan)       flage |= SDL_WINDOW_VULKAN;
        if (render.metal)        flage |= SDL_WINDOW_METAL;
        if (transparent)         flage |= SDL_WINDOW_TRANSPARENT;
        if (not_focusable)       flage |= SDL_WINDOW_NOT_FOCUSABLE;
    }
}
    