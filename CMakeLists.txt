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
    D:/mingw64/RGFW-1.8.0_win64_mingw-w64/include
)

# 链接文件
target_link_libraries(
    MemorySea
)