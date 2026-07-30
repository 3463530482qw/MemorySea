namespace youklx {
    void Vulkan::init(itvinfo& ivinfo) {
        createInstance(ivinfo);
        pickPhysicalDevice();
    }
}