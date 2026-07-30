void createInstance(itvinfo& ivinfo);
void pickPhysicalDevice();
void createLogicalDevice(uint32_t graphicsFamilyIndex);
uint32_t ratePhysicalDevice(const vk::raii::PhysicalDevice& device);
void init(itvinfo& ivinfo);