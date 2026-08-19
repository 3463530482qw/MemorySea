from pathlib import Path
import subprocess
import glob

## 默认路径
mopath = Path.cwd()

## c++文件路径
main = Path("apitest.cpp")

# 生成的可执行文件路径
run = Path("build/MemorySea.exe")

#创建构建文件夹
Path("./build").mkdir(exist_ok=True)

# 编译主程序
print("=== 编译主程序 ===")

# 编译器命令(经过 ccache 缓存,没改过的文件秒过)
gpp = ["ccache", "g++"]

# spine 运行时源码(spine-cpp 递归 + spine-sdl 顶层)
spine_sources = (
    glob.glob("D:/mingw64/spine-runtimes-4.3/spine-cpp/src/**/*.cpp", recursive=True) +
    glob.glob("D:/mingw64/spine-runtimes-4.3/spine-sdl/src/*.cpp")
)

include_dirs = [
    "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include",
    "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include/SDL3",
    "D:/mingw64/inih-r62/inih-r62",
    "D:/mingw64/spine-runtimes-4.3/spine-cpp/include",
    "D:/mingw64/spine-runtimes-4.3/spine-sdl/src",
    "D:/mingw64/stb-master/stb-master",
    "D:/Luos",
    str(mopath),
    "C:/vulkan/Include",
]

# spine 预编译静态库:第三方代码不会变,只编一次,之后只链接
# 如需强制重建(比如升级 spine),删掉 build/libspine.a 即可
spine_lib = mopath / "build" / "libspine.a"
spine_obj_dir = mopath / "build" / "spine_obj"
if not spine_lib.exists():
    print(f"=== 编译 spine 静态库(一次性,如需重建请删除 {spine_lib.name}) ===")
    spine_obj_dir.mkdir(parents=True, exist_ok=True)
    objs = []
    for f in spine_sources:
        p = Path(f)
        obj = spine_obj_dir / f"{p.parent.name}_{p.stem}.o"
        subprocess.run([
            *gpp, "-std=c++23", "-O2", "-DNDEBUG",
            "-finput-charset=UTF-8", "-fexec-charset=UTF-8",
            "-c", str(f), "-o", str(obj),
            *[f"-I{i}" for i in include_dirs],
        ], check=True)
        objs.append(obj)
    subprocess.run(["x86_64-w64-mingw32-ar", "rcs", str(spine_lib), *[str(o) for o in objs]], check=True)
    print(f"spine 静态库生成: {spine_lib}")
else:
    print(f"=== 使用已编译的 spine 静态库(如需重建请删除 {spine_lib.name}) ===")

# 导出所有符号,生成导入库(场景 DLL 链接用)
import_lib = mopath / "build" / "libMemorySea.dll.a"
link_options = [
    f"-Wl,--export-all-symbols,--out-implib,{import_lib.as_posix()}",
    "-L", "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/lib",
    "C:/vulkan/Lib/vulkan-1.lib",
    "-lSDL3",
    "-lwinmm",
]

# 主程序拆成两步:先 ccache 编译 .o(命中缓存则秒过),再纯链接(0.3s)
main_obj = mopath / "build" / "apitest.o"
subprocess.run([
    *gpp,
    "-std=c++23",
    "-finput-charset=UTF-8",
    "-fexec-charset=UTF-8",
    "-DNDEBUG",
    "-c", str(main), "-o", str(main_obj),
    *[f"-I{i}" for i in include_dirs],
], check=True)

gpp_cmd = [
    "g++",
    "-std=c++23",
    "-DNDEBUG",
    "-o", str(run),
    str(main_obj),
    # --whole-archive: 让 spine 全部符号进 DLL,场景模块才能通过导入库链接到任意 spine 类
    "-Wl,--whole-archive", str(spine_lib), "-Wl,--no-whole-archive",
    *link_options,
]

subprocess.run(gpp_cmd, check=True)
print(f"主程序编译完成: {run}")

# 编译所有场景模块
print("=== 编译场景模块 ===")
sence_dir = Path("sence")
for bulid_py in sence_dir.glob("*/bulid.py"):
    scene_name = bulid_py.parent.name
    print(f"编译场景: {scene_name}")
    subprocess.run([
        "python", str(bulid_py)
    ], check=True)

print(f"构建完成: {run}")
