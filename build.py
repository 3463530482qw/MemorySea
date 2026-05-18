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

subprocess.run([
    "cmake",
    "-G", "MinGW Makefiles",     # 指定使用 MinGW 生成器
    "-S", str(mopath),           # 源代码目录（当前目录）
    "-B", str(mopath / "build")  # 构建输出目录（./build）
], check=True)

subprocess.run([
    "cmake",
    "--build", str(mopath / "build")  # 在 build 目录中执行构建
], check=True)


#sdl动态链接库位置与目标位置
sdldll = Path("D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/bin/SDL3.dll")
sdldlldst = Path("./build")

try:
    shutil.copy(sdldll, sdldlldst)
    print("文件复制成功！")
except FileNotFoundError:
    print("源文件不存在！")
except PermissionError:
    print("没有权限操作该文件或目录！")

subprocess.run([
    str(run)],
    check=True
)