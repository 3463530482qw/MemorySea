vk::raii::Semaphore& 图像可用信号量{imageAvailableSemaphore};
vk::raii::Semaphore& 渲染完成信号量{renderFinishedSemaphore};
vk::raii::Fence& 飞行围栏{inFlightFence};
