namespace youklx {
    void Wvulkan::init(Vulkan& vulkan) {
        #include "method/inlinevar.inl"
        #include "method/createsurface.inl"
        #include "method/findgraphicsqueuefamily.inl"
        swapchain.createSwapchain();
    }
}