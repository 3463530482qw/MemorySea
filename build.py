from pathlib import Path
import subprocess
import shutil

## 默认路径
mopath = Path.cwd()

## c++与cmake文件路径
main = Path("main.cpp")
cmake = Path("CMakeLists.txt")

# 生成的可执行文件路径
run = Path("build/MemorySea.exe")

#创建构建文件夹
Path("./build").mkdir(exist_ok=True)

# 编译着色器
print("=== 编译着色器 ===")
subprocess.run([
    "python", str(mopath / "shaders" / "compile.py")
], check=True)

# 复制着色器到 build 目录
shaders_build = Path("./build/shaders")
shaders_build.mkdir(parents=True, exist_ok=True)

subprocess.run([
    "cmake",
    "-G", "MinGW Makefiles",     # 指定使用 MinGW 生成器
    "-DCMAKE_BUILD_TYPE=Release",# 开启 Release 模式
    "-S", str(mopath),           # 源代码目录（当前目录）
    "-B", str(mopath / "build")  # 构建输出目录（./build）
], check=True)

subprocess.run([
    "cmake",
    "--build", str(mopath / "build")  # 在 build 目录中执行构建
], check=True)


#sdl动态链接库位置与目标位置
sdldll = [ 
    Path("C:/Windows/WinSxS/x86_microsoft-windows-vulkan-loader_31bf3856ad364e35_10.0.26100.1_none_b0165e7e6d4a049a/vulkan-1.dll"),
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