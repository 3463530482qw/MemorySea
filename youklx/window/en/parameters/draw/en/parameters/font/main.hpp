namespace youklx {
    class Fontcmd {   // 字体绘制命令子模块:只负责字体的参数与生成命令
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
    };
    using 字体绘制命令 = Fontcmd;
}
