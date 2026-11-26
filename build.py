import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent
sys.path.insert(0, str(ROOT))

from build_config import (
    BUILD,
    COMPILER,
    CXX_FLAGS,
    RUNTIME_DIRS,
    RUNTIME_DLLS,
    SDL,
    SIMDJSON,
    SPINE,
    VULKAN,
    include_args,
    run,
)

def build_spine() -> Path:
    lib = BUILD / "libspine.a"
    if lib.is_file():
        print("=== 使用已编译的 spine 静态库 ===")
        return lib

    print("=== 编译 spine 静态库(一次性) ===")
    sources = sorted((SPINE / "spine-cpp/src").rglob("*.cpp")) + sorted((SPINE / "spine-sdl/src").glob("*.cpp"))
    obj_dir = BUILD / "spine_obj"
    obj_dir.mkdir(parents=True, exist_ok=True)
    objects = []
    for source in sources:
        obj = obj_dir / f"{source.parent.name}_{source.stem}.o"
        run([
            *COMPILER, *CXX_FLAGS, "-O2",
            "-c", source.as_posix(), "-o", obj.as_posix(),
            *include_args(),
        ])
        objects.append(obj.as_posix())
    run(["x86_64-w64-mingw32-ar", "rcs", lib.as_posix(), *objects])
    print(f"spine 静态库: {lib}")
    return lib

def build_simdjson() -> Path:
    lib = BUILD / "libsimdjson.a"
    if lib.is_file():
        print("=== 使用已编译的 simdjson 静态库 ===")
        return lib

    print("=== 编译 simdjson 静态库(一次性) ===")
    obj = BUILD / "simdjson.o"
    run([
        *COMPILER, *CXX_FLAGS, "-O2",
        "-c", (SIMDJSON / "src/simdjson.cpp").as_posix(), "-o", obj.as_posix(),
        *include_args(SIMDJSON / "src"),
    ])
    run(["x86_64-w64-mingw32-ar", "rcs", lib.as_posix(), obj.as_posix()])
    print(f"simdjson 静态库: {lib}")
    return lib

def build_main(spine_lib: Path, simdjson_lib: Path) -> Path:
    print("=== 编译主程序 ===")
    main_obj = BUILD / "MemorySea.o"
    exe = BUILD / "MemorySea.exe"
    run([
        *COMPILER, *CXX_FLAGS,
        "-c", (ROOT / "main.cpp").as_posix(), "-o", main_obj.as_posix(),
        *include_args(),
    ])
    run([
        "g++", "-std=c++23", "-DNDEBUG",
        "-o", exe.as_posix(), main_obj.as_posix(),
        # --whole-archive:spine 与 simdjson 的符号全量进 exe,场景 DLL 才能经导入库链到
        "-Wl,--whole-archive", spine_lib.as_posix(), "-Wl,--no-whole-archive",
        "-Wl,--whole-archive", simdjson_lib.as_posix(), "-Wl,--no-whole-archive",
        f"-Wl,--export-all-symbols,--out-implib,{(BUILD / 'libMemorySea.dll.a').as_posix()}",
        "-L", (SDL / "lib").as_posix(),
        (VULKAN / "Lib/vulkan-1.lib").as_posix(),
        "-lSDL3", "-lwinmm",
    ])
    print(f"主程序: {exe}")
    return exe

def build_shaders() -> None:
    print("=== 编译着色器 ===")
    subprocess.run([sys.executable, (ROOT / "shaders/compile.py").as_posix()], check=True)

def build_scenes() -> None:
    scripts = sorted((ROOT / "sence").glob("*/build.py"))
    if not scripts:
        print("=== 没有场景脚本 ===")
        return
    for script in scripts:
        subprocess.run([sys.executable, script.as_posix()], check=True)

def sync_runtime() -> None:
    print("=== 同步运行库与资源 ===")
    for dll in RUNTIME_DLLS:
        if dll.is_file():
            shutil.copy2(dll, BUILD / dll.name)
            print(f"dll: {dll.name}")
        else:
            print(f"警告: 缺少 {dll}")
    for name in RUNTIME_DIRS:
        source = ROOT / name
        if not source.is_dir():
            print(f"警告: 缺少资源目录 {name}/")
            continue
        shutil.copytree(source, BUILD / name, dirs_exist_ok=True)
        print(f"资源: {name}/")

def main() -> None:
    BUILD.mkdir(exist_ok=True)
    spine_lib = build_spine()
    simdjson_lib = build_simdjson()
    build_main(spine_lib, simdjson_lib)
    build_shaders()
    build_scenes()
    sync_runtime()
    print("构建完成: build/MemorySea.exe")

if __name__ == "__main__":
    main()
