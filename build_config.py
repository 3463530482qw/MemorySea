from pathlib import Path
import subprocess

## 项目根目录与产物目录:都按本文件位置算,不受工作目录影响
ROOT = Path(__file__).resolve().parent
BUILD = ROOT / "build"

## 第三方库固定位置
MINGW = Path("D:/mingw64")
SDL = MINGW / "SDL3-3.4.8/x86_64-w64-mingw32"
SIMDJSON = MINGW / "simdjson-4.6.7/simdjson-4.6.7"
SPINE = MINGW / "spine-runtimes-4.3"
INIH = MINGW / "inih-r62/inih-r62"
STB = MINGW / "stb-master/stb-master"
LUOS = Path("D:/Luos")
VULKAN = Path("C:/vulkan")
GLSLC = VULKAN / "Bin/glslc.exe"
SHADER_DIR = ROOT / "shaders"
SHADER_OUT = BUILD / "shaders"

## 编译参数:主程序、场景、第三方静态库共用同一套口径
COMPILER = ["ccache", "g++"]
CXX_FLAGS = ["-std=c++23", "-finput-charset=UTF-8", "-fexec-charset=UTF-8", "-DNDEBUG"]
INCLUDE_DIRS = [
    SDL / "include",
    SDL / "include/SDL3",
    INIH,
    SIMDJSON / "include",
    SPINE / "spine-cpp/include",
    SPINE / "spine-sdl/src",
    STB,
    LUOS,
    ROOT,
    VULKAN / "Include",
]

## 运行期同步清单:来源缺失时只告警,不打断构建
RUNTIME_DLLS = [
    Path("C:/Windows/System32/vulkan-1.dll"),
    SDL / "bin/SDL3.dll",
    MINGW / "bin/libunwind.dll",
    MINGW / "bin/libc++.dll",
]
RUNTIME_DIRS = ["json", "image", "font"]

def include_args(*extra: Path) -> list[str]:
    return [f"-I{path.as_posix()}" for path in (*INCLUDE_DIRS, *extra)]

def run(command: list[str]) -> None:
    subprocess.run(command, check=True)

def build_scene(scene_dir: Path) -> Path:
    """场景入口共用:一个 .cpp 编一个 DLL,输出到 build/dll/<名字>/"""
    scene_dir = Path(scene_dir).resolve()
    cpp_files = sorted(scene_dir.glob("*.cpp"))
    if len(cpp_files) != 1:
        raise RuntimeError(f"场景目录只允许一个 .cpp: {scene_dir} -> {[path.name for path in cpp_files]}")

    import_lib = BUILD / "libMemorySea.dll.a"
    if not import_lib.is_file():
        raise RuntimeError(f"缺少导入库 {import_lib},先跑根目录 build.py")

    main_cpp = cpp_files[0]
    name = main_cpp.stem
    out_dir = BUILD / "dll" / name
    out_dir.mkdir(parents=True, exist_ok=True)
    obj = out_dir / f"{name}.o"
    dll = out_dir / f"{name}.dll"

    print(f"=== 编译场景: {name} ===")
    run([
        *COMPILER, *CXX_FLAGS, "-Os", "-DEXPORT=__declspec(dllexport)",
        "-c", main_cpp.as_posix(), "-o", obj.as_posix(),
        *include_args(),
    ])
    run([
        "g++", "-shared", "-Os", "-s", "-std=c++23", "-DNDEBUG",
        "-o", dll.as_posix(), obj.as_posix(), import_lib.as_posix(),
        "-L", (SDL / "lib").as_posix(),
        (VULKAN / "Lib/vulkan-1.lib").as_posix(),
        "-lSDL3", "-lwinmm",
    ])
    print(f"场景 DLL: {dll}")
    return dll
