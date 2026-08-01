vk::raii::Device* device{nullptr};
vk::raii::Semaphore imageAvailableSemaphore{nullptr};
vk::raii::Semaphore renderFinishedSemaphore{nullptr};
vk::raii::Fence inFlightFence{nullptr};