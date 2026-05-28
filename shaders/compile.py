"""
着色器编译脚本
使用 glslc 将 GLSL 着色器编译为 SPIR-V 字节码 (.spv)
输出到 build/shaders/ 目录
"""
import subprocess
from pathlib import Path

# glslc 编译器路径
GLSLC = Path("C:/Vulkan/Bin/glslc.exe")

# 着色器源文件目录
SHADER_DIR = Path(__file__).parent

# 输出目录
OUTPUT_DIR = Path.cwd() / "build" / "shaders"

def compile_shader(src: Path, dst: Path, stage: str) -> bool:
    """编译单个着色器文件"""
    print(f"编译 {stage} 着色器: {src.name} -> {dst.name}")
    try:
        subprocess.run(
            [str(GLSLC), str(src), "-o", str(dst)],
            check=True
        )
        print(f"  ✓ {stage} 着色器编译成功")
        return True
    except subprocess.CalledProcessError as e:
        print(f"  ✗ {stage} 着色器编译失败: {e}")
        return False
    except FileNotFoundError:
        print(f"  ✗ 找不到 glslc 编译器: {GLSLC}")
        print(f"    请检查 Vulkan SDK 是否安装在 C:/Vulkan/")
        return False

def main():
    # 确保输出目录存在
    OUTPUT_DIR.mkdir(parents=True, exist_ok=True)

    print(f"=== 着色器编译 ===")
    print(f"源目录: {SHADER_DIR}")
    print(f"输出目录: {OUTPUT_DIR}")
    print()

    success = True

    # 编译顶点着色器
    vert_src = SHADER_DIR / "shader.vert"
    vert_dst = OUTPUT_DIR / "shader.vert.spv"
    if vert_src.exists():
        success &= compile_shader(vert_src, vert_dst, "顶点")
    else:
        print(f"  ✗ 找不到顶点着色器: {vert_src}")
        success = False

    # 编译片段着色器
    frag_src = SHADER_DIR / "shader.frag"
    frag_dst = OUTPUT_DIR / "shader.frag.spv"
    if frag_src.exists():
        success &= compile_shader(frag_src, frag_dst, "片段")
    else:
        print(f"  ✗ 找不到片段着色器: {frag_src}")
        success = False

    print()
    if success:
        print("=== 所有着色器编译完成 ===")
    else:
        print("=== 着色器编译失败 ===")
        exit(1)

if __name__ == "__main__":
    main()