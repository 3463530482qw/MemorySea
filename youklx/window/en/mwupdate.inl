namespace youklx {
    void Window::mwupdate(int mx, int my) {
        w = mx;
        h = my;
        wvulkan.commandBuffer.vpH = static_cast<float>(h) * aspectratio;
        if (static_cast<float>(w) >= wvulkan.commandBuffer.vpH) {
            wvulkan.commandBuffer.vpW = wvulkan.commandBuffer.vpH;
            wvulkan.commandBuffer.vpH = wvulkan.commandBuffer.vpH / aspectratio;
            dix = (static_cast<float>(w) - wvulkan.commandBuffer.vpW) / 2.0f;
            diy = 0;
        } else {
            wvulkan.commandBuffer.vpW = static_cast<float>(w);
            wvulkan.commandBuffer.vpH = wvulkan.commandBuffer.vpW / aspectratio;
            diy = (static_cast<float>(h) - wvulkan.commandBuffer.vpH) / 2.0f;
            dix = 0;
        }
        reasc = static_cast<float>(wvulkan.commandBuffer.vpW) / static_cast<float>(mlx);
        wvulkan.framebufferResized = true;
        wvulkan.pendingWidth  = static_cast<uint32_t>(w);
        wvulkan.pendingHeight = static_cast<uint32_t>(h);
        wvulkan.commandBuffer.vpX = static_cast<int32_t>(dix);
        wvulkan.commandBuffer.vpY = static_cast<int32_t>(diy);
    }
}