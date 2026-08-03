namespace youklx {
    void Compiler::work(int cargc, char** cargv) {
        argc = cargc;
        argv = cargv;
        if (argc > 1 && std::string(argv[1]) == "uninstaller.yokc") {
            unregistry();
            return;
        }
        registry();
    }
}