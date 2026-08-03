            // 读入源码文件到 src_buf,打开失败返回 false
            bool load_source(const char* path);
            // 词法分析:取下一个 token
            void next();
            // 表达式解析(lev 为当前允许的最低运算符优先级,用优先级爬升法)
            void expr(int64_t lev);
            // 语句解析
            void stmt();
            // 全局声明解析 + 编译(原版 main 的解析部分)
            void parse();
            // 虚拟机执行
            void run();