cmake_minimum_required(VERSION 3.28)
project(MemorySea)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SPINE_SOURCES 
    "D:/mingw64/spine-runtimes-4.3/spine-cpp/src/*.cpp"
    "D:/mingw64/spine-runtimes-4.3/spine-sdl/src/*.cpp"
)

add_executable(MemorySea main.cpp ${SPINE_SOURCES})

include_directories(
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/include/SDL3
    D:/mingw64/inih-r62/inih-r62
    D:/mingw64/spine-runtimes-4.3/spine-cpp/include
    D:/mingw64/spine-runtimes-4.3/spine-sdl/src
    D:/mingw64/stb-master/stb-master
)

target_link_libraries(MemorySea
    D:/mingw64/SDL3-3.4.8/x86_64-w64-mingw32/lib/libSDL3.dll.a
)

# 关键：导出所有符号，生成导入库
target_link_options(MemorySea PRIVATE -Wl,--export-all-symbols,--out-implib,libMemorySea.dll.a)