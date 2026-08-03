from pathlib import Path
import subprocess
import shutil
import glob

## 默认路径
mopath = Path.cwd()

## c++文件路径
main = Path("main.cpp")

# 生成的可执行文件路径
run = Path("build/MemorySea.exe")

#创建构建文件夹
Path("./build").mkdir(exist_ok=True)

# 编译着色器
print("=== 编译着色器 ===")
subprocess.run([
    "python", str(mopath / "shaders" / "compile.py")
], check=True)

# 编译主程序
print("=== 编译主程序 ===")

# spine 运行时源码（spine-cpp 递归 + spine-sdl 顶层）
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
    str(mopath),
    "C:/vulkan/Include",
]

# 导出所有符号，生成导入库（场景 DLL 链接用）
import_lib = mopath / "build" / "libMemorySea.dll.a"
link_options = [
    f"-Wl,--export-all-symbols,--out-implib,{import_lib.as_posix()}",
    "-L", "D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/lib",
    "C:/vulkan/Lib/vulkan-1.lib",
    "-lSDL3",
    "-lwinmm",
]

gpp_cmd = [
    "g++",
    "-std=c++23",
    "-finput-charset=UTF-8",
    "-fexec-charset=UTF-8",
    "-DNDEBUG",
    "-o", str(run),
    str(main),
    *spine_sources,
    *[f"-I{i}" for i in include_dirs],
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

#sdl动态链接库位置与目标位置
sdldll = [ 
    Path("C:/Windows/System32/vulkan-1.dll"),
    Path("D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/bin/SDL3.dll"),
    Path("D:/mingw64/bin/libunwind.dll"),
    Path("D:/mingw64/bin/libc++.dll")
]
sdldlldst = Path("./build")
for dst in sdldll:
    try:
        shutil.copy(dst, sdldlldst)
        print(f"dll文件复制成功！目标位置: {dst}")
    except FileNotFoundError:
        print(f"dll源文件不存在: {dst}")
        continue
    except PermissionError:
        print(f"没有权限操作该文件或目录: {dst}")

#配置文件夹复制
ini = Path("ini")
inip = Path("./build/ini")

try:
    shutil.copytree(ini, inip, dirs_exist_ok=True)
    print("配置文件复制成功！")
except FileNotFoundError:
    print("配置源文件不存在！")
except PermissionError:
    print("配置没有权限操作该文件或目录！")

#图片文件夹复制
ini = Path("image")
inip = Path("./build/image")

try:
    shutil.copytree(ini, inip, dirs_exist_ok=True)
    print("图片文件复制成功！")
except FileNotFoundError:
    print("图片源文件不存在！")
except PermissionError:
    print("图片没有权限操作该文件或目录！")

#字体文件复制
ini = Path("font")
inip = Path("./build/font")

try:
    shutil.copytree(ini, inip, dirs_exist_ok=True)
    print("字体文件复制成功！")
except FileNotFoundError:
    print("字体源文件不存在！")
except PermissionError:
    print("字体没有权限操作该文件或目录！")

subprocess.run([
    str(run)],
    check=True
)