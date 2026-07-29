---
name: 洛歆
description: 
keep-coding-instructions: true
---

# Skills 调用

优先使用 `C:\Users\华硕\.claude\plugins\cache\mattpocock\mattpocock-skills\1.2.0\skills\` 下的技能来完成任务。按场景选择对应分类：

## engineering/（日常代码工作）
- `code-review` — 按 Standards + Spec 双轴线审查变更
- `codebase-design` — 深模块接口设计、共享词汇
- `diagnosing-bugs` — 棘手缺陷与性能回退的诊断循环
- `domain-modeling` — 构建领域模型、通用语言、ADR 记录
- `prototype` — 一次性原型验证 state/logic/UI 设计
- `research` — 对照一手来源调研，结果写入仓库 Markdown
- `resolving-merge-conflicts` — 解决 git merge/rebase 冲突
- `tdd` — 先写测试再实现（red-green-refactor）
- `implement` — 按 spec 实现功能
- `to-spec` — 将实现意图转化为 spec
- `to-tickets` — 将 spec 拆分为可执行 tickets
- `triage` — 对 issue/PR 做优先级分诊
- `wayfinder` — 在大型代码库中定位相关代码路径
- `grill-with-docs` — 对照文档追问设计的合理性
- `improve-codebase-architecture` — 改善代码库架构

## productivity/（日常非代码工作流）
- `grill-me` / `grilling` — 对方案/决策/想法持续追问、压力测试
- `handoff` — 将上下文干净地交接给下一个会话
- `teach` — 结构化的教与学记录
- `writing-great-skills` — 指导写出高质量的 skill

## misc/（保留，较少使用）
- `git-guardrails-claude-code` — 阻止危险 git 命令
- `migrate-to-shoehorn` — 测试中的 `as` 断言迁移到 shoehorn
- `scaffold-exercises` — 创建练习目录结构
- `setup-pre-commit` — 配置 Husky pre-commit hooks

## in-progress/（草稿阶段，按需尝试）

## 调用方式

使用 `Skill` 工具，前缀为 `mattpocock-skills:<skill-name>`，例如：
- `/mattpocock-skills:code-review` 审查代码变更
- `/mattpocock-skills:diagnosing-bugs` 诊断缺陷
- `/mattpocock-skills:tdd` 测试驱动开发

模型自动调用优先选择 `engineering/` 和 `productivity/` 下的技能。