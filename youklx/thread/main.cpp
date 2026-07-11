namespace youklx {
    template<uint8_t tnths>
    Thread<tnths>::Thread() {
        auto haco = std::thread::hardware_concurrency();
        haco = haco == 0 ? 4 : haco;
        nths = static_cast<uint8_t>(haco > 2 ? haco - 2 : 1);
        if (nths > mnths) nths = mnths;
    }
}