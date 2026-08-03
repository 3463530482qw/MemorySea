namespace youklx {
    void Compiler::work(int vargc, char** vargv) {
        argc = vargc;
        argv = vargv;
        if (argc > 1 && std::string(argv[1]) == "uninstaller.yokc") {
            disassociate();
            return;
        }
        associate();
        std::string path = argc > 1 ? argv[1] : default_path();
        if (path.empty()) throw std::runtime_error("未指定脚本,且 exe 同目录下没有 main.yokc");
        read(path);
        lex();
        result = expr();
        std::cout << result << std::endl;
        std::cin.get();
    }
}
