namespace youklx {
    // 读入源码文件到 src_buf;打开失败返回 false
    bool Compiler::load_source(const char* path) {
        std::ifstream f(path, std::ios::binary);
        if (!f) return false;
        src_buf.resize(poolsz);
        f.read(src_buf.data(), poolsz - 1);
        int64_t n = (int64_t)f.gcount();
        if (n <= 0) throw std::runtime_error("read() returned 0");
        src_buf[n] = 0; // 字符串终止符,词法分析依赖
        return true;
    }

    void Compiler::work(int cargc, char** cargv) {
        argc = cargc;
        argv = cargv;
        // 无参数:注册 .yokc 文件关联
        if (argc <= 1) {
            registry();
            return;
        }
        // 卸载文件关联
        if (std::string(argv[1]) == "uninstaller.yokc") {
            unregistry();
            return;
        }
        // c4 选项:[-s] [-d] file,其后参数作为被编译程序的 argv
        int i = 1;
        if (argc > i && argv[i][0] == '-' && argv[i][1] == 's') { src = 1; ++i; }
        if (argc > i && argv[i][0] == '-' && argv[i][1] == 'd') { debug = 1; ++i; }
        if (argc <= i) throw std::runtime_error("usage: MemorySea [-s] [-d] file");
        if (!load_source(argv[i])) throw std::runtime_error(std::string("could not open(") + argv[i] + ")");
        // 剩余参数作为用户程序 argc/argv(argv[0] 是源码文件名)
        argc = cargc - i;
        argv = cargv + i;

        // 分配四个内存池(vector 值初始化全 0,替代原版 malloc+memset)
        sym_pool.resize(poolsz);
        text_pool.resize(poolsz);
        data_pool.resize(poolsz);
        stack_pool.resize(poolsz);
        sym = sym_pool.data();    // 符号表池
        le = e = text_pool.data(); // 代码池
        data = data_pool.data();  // 数据段池

        parse(); // 编译
        run();   // 执行
    }
}
