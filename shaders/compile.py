"""
着色器编译脚本
使用 glslc 将 GLSL 着色器编译为 SPIR-V 字节码 (.spv)
输出到 build/shaders/ 目录
"""
import subprocess
from pathlib import Path

GLSLC = Path("C:/Vulkan/Bin/glslc.exe")
SHADER_DIR = Path(__file__).parent
OUTPUT_DIR = Path.cwd() / "build" / "shaders"

def compile_shader(src: Path, dst: Path, stage: str) -> bool:
    print(f"编译 {stage} 着色器: {src.name} -> {dst.name}")
    try:
        subprocess.run([str(GLSLC), str(src), "-o", str(dst)], check=True)
        print(f"  ✓ {stage} 着色器编译成功")
        return True
    except subprocess.CalledProcessError as e:
        print(f"  ✗ {stage} 着色器编译失败: {e}")
        return False
    except FileNotFoundError:
        print(f"  ✗ 找不到 glslc 编译器: {GLSLC}")
        return False

def main():
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)
    print(f"=== 着色器编译 ===")
    print(f"源目录: {SHADER_DIR}")
    print(f"输出目录: {OUTPUT_DIR}")
    print()
    success = True

    # line.vert + line.frag
    success &= compile_shader(SHADER_DIR/"line.vert", OUTPUT_DIR/"line.vert.spv", "line顶点")
    success &= compile_shader(SHADER_DIR/"line.frag", OUTPUT_DIR/"line.frag.spv", "line片段")

    # image.vert + image.frag
    success &= compile_shader(SHADER_DIR/"image.vert", OUTPUT_DIR/"image.vert.spv", "image顶点")
    success &= compile_shader(SHADER_DIR/"image.frag", OUTPUT_DIR/"image.frag.spv", "image片段")

    print()
    if success:
        print("=== 所有着色器编译完成 ===")
    else:
        print("=== 着色器编译失败 ===")
        exit(1)

if __name__ == "__main__":
    main()