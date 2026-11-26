import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from build_config import GLSLC, SHADER_DIR, SHADER_OUT

def compile_shader(source: Path, output: Path) -> bool:
    if output.is_file() and output.stat().st_mtime >= source.stat().st_mtime:
        print(f"跳过(已最新): {output.name}")
        return True
    print(f"着色器: {source.name} -> {output.name}")
    result = subprocess.run([GLSLC.as_posix(), source.as_posix(), "-o", output.as_posix()])
    if result.returncode != 0:
        print(f"失败: {source.name}")
        return False
    return True

def main() -> int:
    if not GLSLC.is_file():
        print(f"找不到 glslc: {GLSLC}")
        return 1
    SHADER_OUT.mkdir(parents=True, exist_ok=True)
    sources = sorted(SHADER_DIR.glob("*.vert")) + sorted(SHADER_DIR.glob("*.frag"))
    failed = [source.name for source in sources if not compile_shader(source, SHADER_OUT / f"{source.name}.spv")]
    if failed:
        print("着色器失败: " + ", ".join(failed))
        return 1
    print(f"着色器完成: {len(sources)} 个")
    return 0

if __name__ == "__main__":
    sys.exit(main())
