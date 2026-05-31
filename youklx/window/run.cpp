namespace youklx {
    Window& Window::run() {
        keyboard.beginFrame();
        mouse.beginFrame();

        while (SDL_PollEvent(&pe)) {
            switch (pe.type) {
                case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                    isrun = false;
                    break;
                case SDL_EVENT_QUIT:
                    isrun = false;
                    break;

                // ---- 键盘 ----
                case SDL_EVENT_KEY_DOWN:
                    keyboard.setDown(pe.key.key);
                    break;
                case SDL_EVENT_KEY_UP:
                    keyboard.setUp(pe.key.key);
                    break;

                // ---- 鼠标移动 ----
                case SDL_EVENT_MOUSE_MOTION:
                    // 将 SDL 物理像素坐标转换为逻辑视图坐标
                    if (w > 0 && h > 0 && stsizew > 0 && stsizeh > 0) {
                        mouse.setPos(
                            static_cast<float>(pe.motion.x) * stsizew / w,
                            static_cast<float>(pe.motion.y) * stsizeh / h
                        );
                    } else {
                        mouse.setPos(
                            static_cast<float>(pe.motion.x),
                            static_cast<float>(pe.motion.y)
                        );
                    }
                    break;

                // ---- 鼠标按键 ----
                case SDL_EVENT_MOUSE_BUTTON_DOWN:
                    mouse.setDown(pe.button.button);
                    break;
                case SDL_EVENT_MOUSE_BUTTON_UP:
                    mouse.setUp(pe.button.button);
                    break;

                // ---- 鼠标滚轮 ----
                case SDL_EVENT_MOUSE_WHEEL:
                    mouse.addWheel(pe.wheel.x, pe.wheel.y);
                    break;

                default:
                    break;
            }
        }

        mouse.endFrame();

        time.update();
        return *this;
    }
}
