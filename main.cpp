#include "vmain.inl"

int main(int argc, char** argv) {
    youklx::init();
    youklx::Compiler compiler;
    compiler.work(argc, argv);
}