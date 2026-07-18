# Decisions — 架构决策记录（ADR）

> Architecture Decision Records — 记录项目中的重要技术决策。

---

## ADR-0001：采用 AppController 作为系统唯一协调器

| 属性 | 内容 |
|------|------|
| **编号** | ADR-0001 |
| **日期** | 2026-07-18 |
| **标题** | 采用 AppController 作为系统唯一协调器（Orchestrator） |
| **状态** | Accepted |

### 背景

项目包含多个 Manager 和 Service 模块，需要一个统一的组件来管理模块的初始化顺序和主循环调度。避免各模块之间直接相互调用导致的耦合。

### 决策

采用 AppController 作为系统唯一的 orchestrator：

- 持有所有 Manager 和 Service 的值类型成员变量
- 在 `begin()` 中按依赖顺序初始化所有模块
- 在 `update()` 中按固定顺序调度所有模块的周期性更新
- 协调模块间数据流（Service → UIManager → HomeScreen）

### 原因

1. 集中管理：所有模块的初始化和调度逻辑在一个地方，易于理解和维护
2. 依赖顺序可控：显式按顺序调用 begin()，避免隐式依赖问题
3. 单线程安全：无需考虑并发问题
4. 适合嵌入式：开销小，不需要 RTOS 或事件系统
5. 易于扩展：添加新模块只需在 AppController 中添加成员变量 + begin/update 调用

### 影响

- 所有模块必须提供 `bool begin()` 和 `void update()` 接口
- 添加新模块需要修改 AppController.h（成员变量）和 AppController.cpp（begin/update 调用）
- 模块间不直接通信，全部通过 AppController 中转
- 不存在模块的动态加载/卸载

---

## ADR-0002：ESP32-S3-WROOM-N16R8 项目采用 N8R8 配置

| 属性 | 内容 |
|------|------|
| **编号** | ADR-0002 |
| **日期** | 2026-07-18 |
| **标题** | 使用 N8R8（8MB Flash / 8MB PSRAM）配置 |
| **状态** | Accepted |

### 背景

ESP32-S3-WROOM-1 模组实测 Flash 为 16MB，但使用 `default_16MB.csv` 分区表会导致 boot loop。当前使用 `default_8MB.csv` 分区表，仅 8MB Flash 可用。

### 决策

- 当前使用 `freenove_esp32_s3_wroom` 板级配置（N8R8: 8MB Flash / 8MB PSRAM）
- 分区表使用 `default_8MB.csv`
- 待解决 16MB 分区表问题后再升级

### 原因

1. 8MB Flash 对当前项目功能足够
2. 避免 boot loop 导致无法开发
3. PSRAM 8MB 对 LVGL 双缓冲足够了

### 影响

- 当前项目仅有 8MB Flash 存储空间
- `platformio.ini` 中配置 `board_build.flash_size = 16MB`（物理 Flash），但 `board_build.partitions = default_8MB.csv`（逻辑分区）
- 约 8MB Flash 空间暂不可用

---

## ADR-0003：采用轮询（Polling）作为系统调度架构

| 属性 | 内容 |
|------|------|
| **编号** | ADR-0003 |
| **日期** | 2026-07-18 |
| **标题** | 采用轮询（Polling）调度，不引入 RTOS |
| **状态** | Accepted |

### 背景

嵌入式系统常见的调度方式有：轮询（Polling）、中断驱动（Interrupt-driven）、RTOS 多任务。需要选择适合本项目的调度方式。

### 决策

采用 Arduino 框架的单线程轮询模型：

- `setup()` 执行一次性初始化
- `loop()` 无限循环调用 `app.update()`
- `app.update()` 按固定顺序轮询调用各模块的 update()
- LVGL 通过 `lv_timer_handler()` 内部管理定时器和渲染刷新

### 原因

1. 简单可靠：单线程无竞态、无死锁、无优先级反转
2. 适合 Arduino 框架：Arduino 本身就是单线程轮询模型
3. 开销小：不需要 RTOS 的上下文切换和内存开销
4. 当前需求足够：不需要实时响应或并行处理
5. LVGL 适配：LVGL 本身设计为在单线程中通过 `lv_timer_handler()` 周期性调用

### 影响

- 所有 `update()` 在单个线程中顺序执行
- 任何 `update()` 的长时间阻塞会影响整个系统
- 不存在中断回调（LVGL 的 flush/touch 回调是同步调用）
- 未来如需异步 WiFi 事件处理，需注意线程安全

---

## ADR-0004：采用分层 Review 开发流程

| 属性 | 内容 |
|------|------|
| **编号** | ADR-0004 |
| **日期** | 2026-07-18 |
| **标题** | 采用 ".h -> Review -> .cpp -> Review -> Integration Test -> Review" 的开发流程 |
| **状态** | Accepted |

### 背景

需要建立一套可靠的开发流程，确保代码质量和架构一致性，同时适合 AI 辅助开发的工作模式。

### 决策

采用三阶段 Review 的开发流程：

1. `.h` 设计 → GPT Review（接口/架构/依赖）
2. `.cpp` 实现 → GPT Review（逻辑/内存/错误处理）
3. Integration Test → GPT Review（功能/性能/回归）

### 原因

1. 先审接口再实现：避免实现后发现接口设计问题
2. 分层责任：每个阶段有明确的检查重点
3. 适合 AI 协作：GPT 在每个阶段执行针对性的 Code Review
4. 减少返工：早期发现问题比后期修复成本低

### 影响

- 每个模块开发需要经过 3 轮 Review
- Review 必须通过才能进入下一阶段
- GPT Review 范围受限于 [DEVELOPMENT_RULES.md](DEVELOPMENT_RULES.md) 中定义的规则
- 禁止"先写代码再补接口"的做法

---

## ADR 模板

后续新增 ADR 时使用以下模板：

```markdown
## ADR-XXXX：标题

| 属性 | 内容 |
|------|------|
| **编号** | ADR-XXXX |
| **日期** | YYYY-MM-DD |
| **标题** | [一句话描述] |
| **状态** | Proposed / Accepted / Deprecated / Superseded |

### 背景
[为什么需要做这个决策]

### 决策
[我们决定做什么]

### 原因
[为什么这样做，为什么不选其他方案]

### 影响
[这个决策会带来什么后果]
```
