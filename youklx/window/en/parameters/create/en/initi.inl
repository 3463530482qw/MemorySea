namespace youklx {
    windowscreateinfo& windowscreateinfo::initi(const std::string& ini, const std::string& ivrtp) {
        INIReader reader(ini);
        if (reader.ParseError() != 0) {
            std::cerr << "Configuration load failed, using default configuration" << std::endl;
        }

        fullscreen          = reader.GetBoolean(ivrtp, "fullscreen", false);
        occluded            = reader.GetBoolean(ivrtp, "occluded", false);
        hidden              = reader.GetBoolean(ivrtp, "hidden", false);
        borderless          = reader.GetBoolean(ivrtp, "borderless", false);
        resizable           = reader.GetBoolean(ivrtp, "resizable", false);
        minimized           = reader.GetBoolean(ivrtp, "minimized", false);
        maximized           = reader.GetBoolean(ivrtp, "maximized", false);
        mouse_grabbed       = reader.GetBoolean(ivrtp, "mouse_grabbed", false);
        input_focus         = reader.GetBoolean(ivrtp, "input_focus", false);
        mouse_focus         = reader.GetBoolean(ivrtp, "mouse_focus", false);
        external            = reader.GetBoolean(ivrtp, "external", false);
        modal               = reader.GetBoolean(ivrtp, "modal", false);
        high_pixel_density  = reader.GetBoolean(ivrtp, "high_pixel_density", false);
        mouse_capture       = reader.GetBoolean(ivrtp, "mouse_capture", false);
        mouse_relative_mode = reader.GetBoolean(ivrtp, "mouse_relative_mode", false);
        always_on_top       = reader.GetBoolean(ivrtp, "always_on_top", false);
        utility             = reader.GetBoolean(ivrtp, "utility", false);
        tooltip             = reader.GetBoolean(ivrtp, "tooltip", false);
        popup_menu          = reader.GetBoolean(ivrtp, "popup_menu", false);
        keyboard_grabbed    = reader.GetBoolean(ivrtp, "keyboard_grabbed", false);
        fill_document       = reader.GetBoolean(ivrtp, "fill_document", false);
        transparent         = reader.GetBoolean(ivrtp, "transparent", false);
        not_focusable       = reader.GetBoolean(ivrtp, "not_focusable", false);
        render.opengl       = reader.GetBoolean(ivrtp, "opengl", false);
        render.vulkan       = reader.GetBoolean(ivrtp, "vulkan", true);
        render.metal        = reader.GetBoolean(ivrtp, "metal", false);

        return *this;
    }
}