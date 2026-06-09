namespace youklx {
    Thread& Thread::init(Window& swi,Vulkan& svk,Draw& sdr,Image& simg,Font& sft) {
        wi = &swi;
        vk = &svk;
        dr = &sdr;
        img = &simg;
        ft = &sft;
        int hcount = std::thread::hardware_concurrency();
        // 求可用线程
        nthread = (hcount <= 4 ? 4 : hcount - 3);
        return *this;
    }
}