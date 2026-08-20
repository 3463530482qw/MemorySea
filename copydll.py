"""
资源复制脚本:将运行所需的 dll 和资源文件夹复制到 build/ 目录
"""
from pathlib import Path
import shutil

def copy_dll():
    # sdl动态链接库位置与目标位置
    sdldll = [
        Path("C:/Windows/System32/vulkan-1.dll"),
        Path("D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/bin/SDL3.dll"),
        Path("D:/mingw64/bin/libunwind.dll"),
        Path("D:/mingw64/bin/libc++.dll")
    ]
    sdldlldst = build_dir()
    for dst in sdldll:
        try:
            shutil.copy(dst, sdldlldst)
            print(f"dll文件复制成功！目标位置: {dst}")
        except FileNotFoundError:
            print(f"dll源文件不存在: {dst}")
            continue
        except PermissionError:
            print(f"没有权限操作该文件或目录: {dst}")

def copy_folder(src_name: str):
    src = Path(__file__).parent / src_name
    dst = build_dir() / src_name
    try:
        shutil.copytree(src, dst, dirs_exist_ok=True)
        print(f"{src_name} 文件夹复制成功！")
    except FileNotFoundError:
        print(f"{src_name} 源文件夹不存在！")
    except PermissionError:
        print(f"{src_name} 没有权限操作该文件夹！")

def build_dir() -> Path:
    return Path(__file__).parent / "build"

def main():
    build_dir().mkdir(parents=True, exist_ok=True)
    print("=== 复制 dll ===")
    copy_dll()
    print("=== 复制资源文件夹 ===")
    copy_folder("json")
    copy_folder("image")
    copy_folder("font")

if __name__ == "__main__":
    main()
