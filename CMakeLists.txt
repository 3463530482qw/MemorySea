cmake_minimum_required(VERSION 3.28) #cmake版本
project(MemorySea) #项目名称
#设置cpp标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 查询cpp文件放入SPINE_SOURCES
file(GLOB_RECURSE SPINE_SOURCES 
    "D:/mingw64/spine-runtimes-4.3/spine-cpp/src/*.cpp"
    "D:/mingw64/spine-runtimes-4.3/spine-sdl/src/*.cpp"
)
# 定义可执行文件目标 MemorySea 与环境
add_executable(MemorySea main.cpp ${SPINE_SOURCES})
# 头文件位置
include_directories(
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include/SDL3
    D:/mingw64/inih-r62/inih-r62
    D:/mingw64/spine-runtimes-4.3/spine-cpp/include
    D:/mingw64/spine-runtimes-4.3/spine-sdl/src
    D:/mingw64/stb-master/stb-master
    D:/MemorySea
    C:/vulkan/Include
)
# 链接静态文件
target_link_libraries(MemorySea
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/lib/libSDL3.dll.a
    C:/vulkan/Lib/vulkan-1.lib 
    winmm
)

# 导出所有符号，生成导入库
target_link_options(MemorySea PRIVATE -Wl,--export-all-symbols,--out-implib,libMemorySea.dll.a)

# 强制 g++ 以 UTF-8 处理源文件和生成的可执行文件（解决中文乱码）
target_compile_options(MemorySea PRIVATE
    -finput-charset=UTF-8
    -fexec-charset=UTF-8
)
