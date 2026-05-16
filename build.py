from pathlib import Path
import subprocess

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

subprocess.run([
    str(run)],
    check=True
)
