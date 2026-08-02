from pathlib import Path
import subprocess

## 默认路径
mopath = Path.cwd()

## 源文件与产物
main_cpp = Path("main.cpp")       # include lua/lua.c 的解释器入口
yoklua = Path("build/yoklua.exe") # 独立 Lua 编译器/解释器

#创建构建目录
Path("./build").mkdir(exist_ok=True)

# 编译 Lua 库源码（排除自带 main() 的 lua.c / luac.c）
lua_dir = Path("lua")
lua_sources = [f for f in lua_dir.glob("*.c") if f.name not in ("lua.c", "luac.c")]
lua_obj_dir = Path("./build/lua")
lua_obj_dir.mkdir(parents=True, exist_ok=True)
lua_objects = []
for src in lua_sources:
    obj = lua_obj_dir / (src.stem + ".o")
    subprocess.run([
        "gcc", "-c", str(src), "-I", str(lua_dir), "-O2",
        "-o", str(obj)
    ], check=True)
    lua_objects.append(str(obj))
print(f"Lua 编译完成: {len(lua_objects)} 个对象文件")

# 编译 main.cpp：-x c 强制按 C 编译（源码实为 lua.c），符号与 lua.o 一致
# 注意：-x c 会作用于其后所有文件，故先单独编译出 .o，再链接
main_obj = Path("./build/yoklua_main.o")
subprocess.run([
    "gcc", "-x", "c", "-std=c23",
    "-finput-charset=UTF-8", "-fexec-charset=UTF-8",
    "-c", str(main_cpp), "-I", str(lua_dir),
    "-o", str(main_obj)
], check=True)

subprocess.run([
    "gcc",
    str(main_obj), *lua_objects,
    "-o", str(yoklua)
], check=True)
print(f"yoklua 编译完成: {yoklua}")
