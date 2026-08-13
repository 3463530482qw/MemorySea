namespace youklx {
    class Fontcmd {   // 字体绘制命令子模块:参数 + 顶点缓冲(设置函数标脏,绘制时脏才重算)
        public:
            #include "en/api/var.inl"
            #include "中文/接口/变量.inl"
        public:
            #include "en/api/function.inl"
            #include "中文/接口/函数.inl"
        private:
            #include "en/api/internal/var.inl"
        public:
            Fontcmd();    
    };
    using 字体绘制命令 = Fontcmd;
}
#include "main.inl"
