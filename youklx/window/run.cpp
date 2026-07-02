namespace youklx {
    Window& Window::run() {
        time.update();
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
                case SDL_EVENT_MOUSE_MOTION: {
                    // 三步映射：窗口坐标 → 交换链坐标 → viewport 内坐标 → 逻辑画布坐标
                    int cw = 0, ch = 0;
                    SDL_GetWindowSize(id, &cw, &ch);
                    if (cw > 0 && ch > 0 && viewportW > 0 && viewportH > 0
                        && stsizew > 0 && stsizeh > 0) {
                        // 交换链完整尺寸 = viewport + 两侧 letterbox（viewport 居中）
                        int chainW = viewportW + viewportX * 2;
                        int chainH = viewportH + viewportY * 2;
                        // 1. 窗口 → 交换链
                        float sx = static_cast<float>(pe.motion.x) * chainW / cw;
                        float sy = static_cast<float>(pe.motion.y) * chainH / ch;
                        // 2. 交换链 → viewport（减去 letterbox 偏移）
                        float vx = sx - viewportX;
                        float vy = sy - viewportY;
                        // 3. viewport → 逻辑画布
                        mouse.setPos(
                            vx * stsizew / viewportW,
                            vy * stsizeh / viewportH
                        );
                    } else {
                        mouse.setPos(
                            static_cast<float>(pe.motion.x),
                            static_cast<float>(pe.motion.y)
                        );
                    }
                    break;
                }

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
                case SDL_EVENT_USER:
                    SDL_SetWindowIcon(id, static_cast<SDL_Surface*>(pe.user.data1));
                    SDL_DestroySurface(static_cast<SDL_Surface*>(pe.user.data1));
                    break;

                default:
                    break;
            }
        }

        mouse.endFrame();

        return *this;
    }
}
