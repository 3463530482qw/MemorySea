namespace youklx {
    void Window::create(windowcreateinfo& creatinfo) {
        unsigned int flags = 0;

        if (creatinfo.wnoborder)           flags |= RGFW_windowNoBorder;
        if (creatinfo.wnoresize)           flags |= RGFW_windowNoResize;
        if (creatinfo.wallowdnd)           flags |= RGFW_windowAllowDND;
        if (creatinfo.whidemouse)          flags |= RGFW_windowHideMouse;
        if (creatinfo.wfullscreen)         flags |= RGFW_windowFullscreen;
        if (creatinfo.wtransparent)        flags |= RGFW_windowTransparent;
        if (creatinfo.wcenter)             flags |= RGFW_windowCenter;
        if (creatinfo.wscaletomonitor)     flags |= RGFW_windowScaleToMonitor;
        if (creatinfo.whide)               flags |= RGFW_windowHide;
        if (creatinfo.wmaximize)           flags |= RGFW_windowMaximize;
        if (creatinfo.wcentercursor)       flags |= RGFW_windowCenterCursor;
        if (creatinfo.wfloating)           flags |= RGFW_windowFloating;
        if (creatinfo.wfocusonshow)        flags |= RGFW_windowFocusOnShow;
        if (creatinfo.wminimize)           flags |= RGFW_windowMinimize;
        if (creatinfo.wfocus)              flags |= RGFW_windowFocus;
        if (creatinfo.wopengl)             flags |= RGFW_windowOpenGL;
        if (creatinfo.wegl)                flags |= RGFW_windowEGL;
        if (creatinfo.wwindowedfullscreen) flags |= RGFW_windowedFullscreen;

        id = RGFW_createWindow(
            creatinfo.wname.c_str(),
            0,
            0,
            creatinfo.width,
            creatinfo.height,
            flags
        );
    }
}