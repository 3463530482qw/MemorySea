---
name: vulkan-init-flow
description: Vulkan 初始化步骤分类：通用/窗口独占/交换链/管线，以及文件拆分方案
metadata:
  type: project
---

Vulkan 初始化按以下顺序执行（参考 `youklx/vulkan1/` 的完整实现）。

## 分类总览

### 通用（在 `youklx/vulkan/` — Vulkan 类，不依赖窗口，整个应用只做一次）

| 步骤 | 说明 | 依赖 |
|---|---|---|
| `createInstance` | 连接驱动，合并 SDL + 用户扩展 | 无 |
| `pickPhysicalDevice` | 选择物理设备（GPU） | instance |
| `createDevice` | 创建逻辑设备 + 获取图形队列 | physicalDevice + surface |
| `createCommandPool` | 命令池，可复用 | device + graphicsFamilyIndex |

### 窗口独占（在 `youklx/window/` — Wvulkan 子对象，需要窗口但只做一次）

| 步骤 | 说明 | 所在 |
|---|---|---|
| `createSurface` | 创建窗口表面，需要 `SDL_Window*` + `Instance&` | `window/en/parameters/wvulkan/` |
| `findGraphicsQueueFamily` | 查找图形队列族索引，需要 `PhysicalDevice&` | `window/en/parameters/wvulkan/` |

> Wvulkan 作为 Window 的成员（`Window::wvulkan`），和 `Time`、`Mouse` 一样是子对象。surface 和 graphicsFamilyIndex 存储在这里，供后续交换链/管线使用。

### 交换链（resize 时必须重建，单独文件 `recreateSwapChain.inl`）

| 步骤 | 说明 | 依赖 |
|---|---|---|
| `createSwapChain` | 交换链 + 图像视图 | device + surface + physicalDevice |
| `createRenderPass` | 渲染通道（依赖交换链格式） | device + swapChainImageFormat |
| `createFramebuffers` | 每张交换链图像一个帧缓冲 | device + renderPass + swapChainImageViews |
| `createCommandBuffers` | 命令缓冲（每帧一个） | device + commandPool |
| `createSyncObjects` | 信号量 + 围栏 | device + swapChainImages.size() |

### 图形管线（单独文件 `createPipeline.inl`）

| 步骤 | 说明 | 依赖 |
|---|---|---|
| `createPipeline` | 着色器、管线布局、描述符池/集、dummy 纹理 | device + renderPass + commandPool + graphicsQueue |

> **注意：** `createPipeline` 依赖 `renderPass`，所以 `recreateSwapChain` 重建 renderPass 后也必须重建 pipeline。vulkan1 的 `recreateSwapChain` 没有重建 pipeline 是一个潜在问题，vulkan/ 新版本应修复这一点。

## 文件结构

```
youklx/
├── vulkan/                          ← 通用 Vulkan 类
│   └── en/
│       ├── instance.inl             ← [x] createInstance
│       ├── pickPhysicalDevice.inl   ← [x] pickPhysicalDevice + ratePhysicalDevice
│       ├── init.inl                 ← 纯初始化调用链
│       ├── createDevice.inl         ← pickPhysicalDevice + createDevice + createCommandPool
│       ├── createPipeline.inl       ← 图形管线（单独文件）
│       ├── createSwapChain.inl      ← 交换链创建
│       └── recreateSwapChain.inl    ← 交换链重建
│
├── window/                          ← Window 类
│   └── en/parameters/wvulkan/       ← [x] Wvulkan 子对象
│       ├── main.hpp
│       ├── en/
│       │   ├── createSurface.inl    ← [x] createSurface
│       │   └── findGraphicsQueueFamily.inl ← [x]
│       └── 中文/接口/
│           ├── 变量.inl
│           └── 函数.inl
```

## 当前进度

- [x] `createInstance` — `vulkan/en/instance.inl`
- [x] `pickPhysicalDevice` — `vulkan/en/pickPhysicalDevice.inl`
- [x] `createSurface` + `findGraphicsQueueFamily` — `window/en/parameters/wvulkan/`
- [ ] `createDevice` — 创建逻辑设备 + 获取图形队列
- [ ] `createCommandPool` — 创建命令池
- [ ] `createSwapChain` — 创建交换链
- [ ] `createRenderPass` — 创建渲染通道
- [ ] `createFramebuffers` — 创建帧缓冲
- [ ] `createCommandBuffers` — 分配命令缓冲
- [ ] `createSyncObjects` — 创建同步对象
- [ ] `createPipeline` — 创建图形管线
- [ ] `recreateSwapChain` — 交换链重建

## 初始化调用链（预期）

```cpp
// 1. 通用部分 (Vulkan)
vulkan.createInstance(ivinfo);
vulkan.pickPhysicalDevice();

// 2. 窗口部分 (Wvulkan)
window.wvulkan.createSurface(window.id, vulkan.instance);
window.wvulkan.findGraphicsQueueFamily(vulkan.physicalDevice);

// 3. 设备创建 (Vulkan，需要窗口给的 graphicsFamilyIndex)
vulkan.createDevice(window.wvulkan.graphicsFamilyIndex);

// 4. 交换链 + 管线 + ...
```

**Why:** 用户正在从 vulkan1 重构出一个参数化的新版本，窗口独占功能归属 Window，通用功能归属 Vulkan。
**How to apply:** 下一步是 `createDevice`，需要从 Wvulkan 获取 graphicsFamilyIndex。
