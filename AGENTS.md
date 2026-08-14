# MemorySea / youklx 项目规范

> 本文件是项目级规范,适用于 `D:\MemorySea` 下的所有工作。修改代码前先通读;具体任务细节与进度以仓库内 `.claude/projects/d--MemorySea/memory/` 的备忘为准。

## 项目概览

- 项目:MemorySea(库部分叫 youklx),Windows 桌面程序,MinGW(g++) + C++23。
- 单头文件式库:整个库由 `youklx/wiall.hpp` 统一组织;主程序入口 `main.cpp` 只 include `vmain.inl`。
- 技术栈:Vulkan(渲染)、SDL3(窗口)、Spine 4.3(骨骼动画)、inih(配置)、stb(图片/字体)。
- 编译必须带 `-finput-charset=UTF-8 -fexec-charset=UTF-8` 与 `-DNDEBUG`;程序输出用 `std::println`,不用 `std::cout`/`printf`。

## 构建

- 根目录 `build.py` 是总入口:ccache + g++ 编译 `apitest.cpp` → `build/MemorySea.exe`;spine 编译成静态库 `build/libspine.a`(要强制重建就删掉它);同时导出导入库 `build/libMemorySea.dll.a` 供场景 DLL 链接。
- 场景模块在 `sence/<场景>/` 下,各自有自己的 `bulid.py`(注意拼写是 bulid,不是 build)。
- 改完场景代码:先在该场景目录跑 `python bulid.py`,再回根目录跑 `python build.py`。
- 第三方依赖路径:SDL3=`D:/mingw64/SDL3-3.4.8`,Vulkan=`C:/vulkan`,Spine=`D:/mingw64/spine-runtimes-4.3`,inih=`D:/mingw64/inih-r62`,stb=`D:/mingw64/stb-master`。

## 目录与文件约定

- 每个模块在 `youklx/<模块>/` 下:`main.hpp` 放类声明(用 #include 把各段拼进类体),`en/` 放英文实现,`中文/` 放中文接口层。
- 类声明固定分段:public 变量(`en/api/var.inl` + `中文/接口/变量.inl`)、public 函数(`en/api/function.inl` + `中文/接口/函数.inl`)、private 段(`en/api/internal/*.inl`)。
- 实现按动作拆成 `en/<动作>.inl`(如 `create.inl`、`load.inl`、`clear.inl`),一个文件只做一个动作;`main.hpp` 末尾按顺序 include 这些实现文件。参数结构体放 `en/parameters/<名>/main.hpp`。
- 中英双语接口:英文 API 是权威实现,中文接口只是 1:1 转发包装(如 `Window& 创建() { return create(); }`);新公开函数必须同时提供中英两个入口。
- 类型别名放 `main.hpp`(如 `using 窗口 = Window;`);`wiall.hpp` 里另有 `namespace 有棵黎夕的 = youklx;`。

## 头文件纪律

- 标准库与第三方 include 只允许写在 `youklx/wiall.hpp`;需要新标准库特性时到 `wiall.hpp` 添加,不要在具体文件里加 #include。
- `STB_TRUETYPE_IMPLEMENTATION` 这类实现宏也只放 `wiall.hpp`。
- 各模块的 `main.hpp` 由 `wiall.hpp` 统一 include;`main.cpp` 只 include `vmain.inl`。

## 代码风格

- 缩进 4 空格,大括号 K&R(同 `main.cpp`);`namespace youklx {` 内整体再缩进一级。
- 类名 PascalCase(Window、Vulkan、Compiler),函数/方法 camelCase(`createInstance`、`pickPhysicalDevice`、`createLogicalDevice`)。
- 项目作者不写注释,现有代码几乎零注释;修改代码时请用中文补充注释,帮助阅读。
- 错误处理:`throw std::runtime_error`(如 `SDL_GetError()` 的消息)。
- 保持与相邻文件一致的写法;`bulid.py` 的拼写、`info.flage` 这类现状写法是项目习惯,不要顺手"修复"。

## Vulkan 约定

- 职责划分:通用 Vulkan 逻辑放 `youklx/vulkan/`(整个应用只做一次),窗口独占的放 `youklx/window/en/parameters/wvulkan/`(surface、graphicsFamilyIndex 存在 Wvulkan 子对象上)。
- 初始化顺序:`createInstance` → `pickPhysicalDevice` → `createSurface` + `findGraphicsQueueFamily` → `createDevice` → `createCommandPool` → `createSwapChain` → `createRenderPass` → `createFramebuffers` → `createCommandBuffers` → `createSyncObjects` → `createPipeline`。
- `createPipeline` 依赖 `renderPass`:`recreateSwapChain` 重建 renderPass 后必须重建 pipeline(vulkan1 旧实现没做,新 `vulkan/` 要修掉这个问题)。
- 详细流程与当前进度见 `.claude/projects/d--MemorySea/memory/vulkan-init-flow.md`。

## 工作流程

- 动手前先通读相关模块,给出多个可选方案供作者挑选,确认完全理解意图后再改;不要只盯着语法错误,作者的设计思路更重要。
- 一次保质保量的修改胜过多次来回;写完必须自查:include 是否进了 `wiall.hpp`、场景改动是否先跑了场景自己的 `bulid.py`、是否按规范补齐中英双接口。
- 修改既有代码时保持克制,只做任务要求的事,不顺手重构无关代码。
