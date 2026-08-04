argc = cargc;
argv = cargv;
if (argc <= 1) {
    registry();
    return;
}
if (std::string(argv[1]) == "uninstaller.yokc") {
    unregistry();
    return;
}
file.open(argv[1]);
if (!file) {
    std::cerr << "无法打开源文件 \"" << argv[1] << "\"\n";
    return false;
}