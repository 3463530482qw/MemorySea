# 最低cmake版本要求
cmake_minimum_required(VERSION 3.28)

# 项目名称
project(MemorySea)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加 Spine 源文件（新增）
file(GLOB_RECURSE SPINE_SOURCES 
    "D:/mingw64/spine-runtimes-4.3/spine-cpp/src/*.cpp"
    "D:/mingw64/spine-runtimes-4.3/spine-sdl/src/*.cpp"
)

# 添加可执行文件（修改这里）
add_executable(
    MemorySea 
    main.cpp
    ${SPINE_SOURCES}
)

# 添加库所在位置
include_directories(
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include/SDL3
    D:/mingw64/inih-r62/inih-r62
    D:/mingw64/spine-runtimes-4.3/spine-cpp/include
    D:/mingw64/spine-runtimes-4.3/spine-sdl/src
    D:/mingw64/stb-master/stb-master
)

# 链接文件（修改这里：用 .dll.a 代替 .dll）
target_link_libraries(
    MemorySea
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/lib/libSDL3.dll.a
)