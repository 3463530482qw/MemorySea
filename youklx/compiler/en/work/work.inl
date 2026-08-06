namespace youklx {
    void Compiler::work(int cargc, char** cargv) {
        #include "init.inl"
        while (!errored && read()) {
            lex.run();
            //lexing();
            stmt();
        }
    }
}
