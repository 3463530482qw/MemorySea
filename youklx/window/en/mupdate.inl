namespace youklx {
    void Window::mupdate(float mx, float my) {
        mouse.x = std::clamp((mx - static_cast<float>(dix)) / reasc, 0.0f, static_cast<float>(mlx));
        mouse.y = std::clamp((my - static_cast<float>(diy)) / reasc, 0.0f, static_cast<float>(mly));
    }
}