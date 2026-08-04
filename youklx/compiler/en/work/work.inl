namespace youklx {
    void Compiler::work(int cargc, char** cargv) {
        #include "init.inl"
        while (read()) {
            lexing();
        }
    }
}
