from pathlib import Path
import subprocess

plugin_dir = Path(__file__).parent
root_dir = plugin_dir.parent.parent   # D:/MemorySea

cpp_files = list(plugin_dir.glob("*.cpp"))
if len(cpp_files) != 1:
    raise RuntimeError(f"需要唯一的 .cpp 文件，找到 {len(cpp_files)} 个: {[f.name for f in cpp_files]}")

main_cpp = cpp_files[0]
proj_name = main_cpp.stem
build_dir = root_dir / "build" / "dll" / proj_name
build_dir.mkdir(parents=True, exist_ok=True)

sources = [str(main_cpp)]
main_import_lib = root_dir / "build" / "libMemorySea.dll.a"

cmd = [
    "g++", "-shared", "-std=c++23", "-Os", "-s",
    "-DEXPORT=__declspec(dllexport)",
    "-o", str(build_dir / f"{proj_name}.dll"),
    *sources,
    "-I", "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include",
    "-I", "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include/SDL3",
    "-I", "D:/mingw64/spine-runtimes-4.3/spine-cpp/include",
    "-I", "D:/mingw64/spine-runtimes-4.3/spine-sdl/src",
    "-I", "D:/mingw64/inih-r62/inih-r62",
    "-I", "D:/mingw64/stb-master/stb-master",
    "-I", str(root_dir),      # 关键：让 #include <youklx/...> 能找到
    str(main_import_lib),
    "-L", "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/lib",
    "-lSDL3"
]

subprocess.run(cmd, check=True)
print(f"{proj_name}.dll 生成在: {build_dir}")