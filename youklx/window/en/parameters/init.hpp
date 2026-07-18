namespace youklx {
    struct w_init { float standardAspectRatio; };
    struct iw_init { std::string ini, ivrtp, itp; };
    using 普通初始化窗口 = w_init;
    using 通过配置初始化窗口 = iw_init;
}