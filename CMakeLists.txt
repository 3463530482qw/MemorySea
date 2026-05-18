# 最cmake低版本要求
cmake_minimum_required(VERSION 3.28)

# 项目名称
project(MemorySea)

# 设置C++标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(
    MemorySea 
    main.cpp
)

# 添加库所在位置
include_directories(
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include
)

# 链接文件
target_link_libraries(
    MemorySea
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/bin/SDL3.dll
)