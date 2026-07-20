if(wininfo.w == 0 && wininfo.h == 0) {
    float target_w, target_h;
    if ((static_cast<float>(mode->w) / static_cast<float>(mode->h)) > 1.7778) {
        target_h = mode->h * 0.9f;
        target_w = target_h * 1.7778;
    } else {
        target_w = mode->w * 0.9f;
        target_h = target_w / 1.7778;
    }
    w = static_cast<int>(target_w);
    h = static_cast<int>(target_h);
} else {
    w = wininfo.w;
    h = wininfo.h;
}
aspectratio = static_cast<float>(w) / static_cast<float>(h);