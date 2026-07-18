# Architecture — 系统架构

> 本文档仅记录系统架构。开发进度见 [ROADMAP.md](ROADMAP.md)，模块详情见 [PROJECT_RECOVERY.md](PROJECT_RECOVERY.md)。

---

## 1. 整体架构

```
+====================================================================+
|                     Application Layer                              |
|                     AppController                                  |
|               (startup orchestration & main loop dispatch)         |
+-------+-------+-------+-------+-------+-------+-------+-----------+
|Display| Touch |  UI   | Power | LVGL  |       |       |  Manager  |
|Mgr    | Mgr   | Mgr   | Mgr   | Port  |       |       |  Layer    |
+-------+-------+-------+-------+-------+-------+-------+-----------+
| Time  | WiFi  |Config |Battery|Weather|SDCard |       |  Service  |
|Svc    |Svc    |Svc    |Svc    |Svc    |Svc    |       |  Layer    |
+-------+-------+-------+-------+-------+-------+-------+           |
| Album | Memo  |  AI   |WebSvr |  OTA  |       |       |           |
|Svc    |Svc    |Svc    |Svc    |Svc    |       |       |           |
+-------+-------+-------+-------+-------+-------+-------+-----------+
|                         UI Layer                                   |
|     UIManager → ScreenBase → HomeScreen (Album/Memo/Chat: TBD)    |
+-------+-------+-------+-------+-------+-------+-------+-----------+
|                        Driver Layer                                |
| DisplayPanelDriver → ESP32DisplayPanelDriver | GT911TouchDriver   |
+-------+-------+-------+-------+-------+-------+-------+-----------+
|                       Hardware Layer                               |
| ESP_Panel (ST7262 RGB LCD) | GT911 Touch  | GPIO / I2C / SPI      |
+====================================================================+
|                    Utility Layer (cross-cutting)                   |
| Logger | BoardConfig | PanelContext | ScreenBase | lv_conf.h       |
| ESP_Panel_Conf.h                                                   |
+====================================================================+
```

---

## 2. 各层职责

### 2.1 Application Layer

**AppController** — 系统唯一的 orchestrator（编排器）。

- 持有所有 Manager 和 Service 的值类型成员变量（共 16 个）
- `begin()`：按依赖顺序初始化所有模块，返回 void（不检查总结果）
- `update()`：按固定顺序调度所有模块的 update()
- 协调模块间数据流：Service 初始化后通过 UIManager setter 推送数据到 HomeScreen
- 不继承任何基类，不实现任何接口
- 文件：`src/modules/app_controller/AppController.h` (50 行), `.cpp` (107 行)

### 2.2 Manager Layer

负责硬件资源管理和系统级状态协调。

| Manager | 职责 | 依赖 |
|---------|------|------|
| DisplayManager | 显示屏初始化、背光亮度、屏幕填充 | DisplayPanelDriver |
| TouchManager | 触摸状态读取、坐标缓存 | GT911TouchDriver |
| UIManager | UI 页面创建、页面切换、数据转发 | HomeScreen |
| PowerManager | 屏幕开关、休眠请求、用户活动跟踪 | Logger, millis() |
| LVGLPort | LVGL 初始化、PSRAM 双缓冲、flush/touch 回调、lv_timer_handler | PanelContext, lvgl |

### 2.3 Service Layer

提供高层业务功能，通常依赖 Manager 层提供的硬件能力。

| Service | 当前状态 | 功能 |
|---------|----------|------|
| TimeService | 占位 | 时间/日期管理（后续 NTP） |
| WiFiService | **真实实现** | STA 模式、connect(10s超时)、scanNetworks |
| ConfigService | **真实实现** | Preferences(NVS) 持久化 |
| BatteryService | 占位 | 电量/充电检测（后续 ADC） |
| WeatherService | 占位 | 天气数据（后续 HTTP API） |
| SDCardService | 占位 | SD 卡挂载（后续 SPI） |
| AlbumService | 部分实现 | 相册轮播索引逻辑已有，无图片数据 |
| MemoService | 部分实现 | 内存 setMemo/clearMemo，无持久化 |
| AIService | 部分实现 | 占位回复，无 API 调用 |
| WebServerService | 占位 | HTTP 服务（后续） |
| OTAService | 占位 | 固件升级（后续） |

### 2.4 UI Layer

- **ScreenBase**：抽象基类，定义页面生命周期接口（`begin/show/hide/update/getName/isVisible`）
- **HomeScreen**：当前唯一实现的 Screen 子类，LVGL 深色主题 6-label 布局
- **UIManager**：页面切换管理（Home/Album/Memo/Chat），当前仅 Home 有实际 UI

### 2.5 Driver Layer

- **DisplayPanelDriver**（门面层）→ **ESP32DisplayPanelDriver**（真实驱动）：两级封装，通过 PanelContext 操作 ESP_Panel LCD
- **GT911TouchDriver**：通过 PanelContext 操作 ESP_Panel Touch

### 2.6 Hardware Layer

- **ESP_Panel**（来自 ESP32_Display_Panel 库）：统一管理 ST7262 RGB LCD + GT911 Touch
- **PanelContext**：持有全局唯一 ESP_Panel 静态实例（`PanelContext.cpp:4`）
- 硬件配置：`ESP_Panel_Conf.h`（LCD 总线/时序/引脚、Touch I2C/引脚、背光 GPIO）

### 2.7 Utility Layer

- **Logger**：全静态方法类，INFO/WARN/ERROR 三级，Serial 输出
- **BoardConfig**：命名空间，全是 constexpr 编译期常量（引脚/时序/参数）
- **PanelContext**：ESP_Panel 单例持有者
- **ScreenBase**：所有 Screen 的抽象基类

---

## 3. 生命周期

所有模块遵循统一的生命周期模式：

```
[静态初始化]  →  AppController 作为全局对象构造，16 个子模块值成员同步构造（仅初始化默认值）
[begin()]     →  AppController::begin() 按依赖顺序调用各模块 begin()，返回 bool
[update()]    →  AppController::update() 每帧按固定顺序调用各模块 update()
[析构]        →  程序退出时自动调用（Arduino 环境通常不触发）
```

- 所有模块生存期 = AppController 生存期 = 整个程序运行期
- 不存在动态创建/销毁
- 不存在延迟初始化（Lazy Init）
- 不存在运行时加载/卸载

---

## 4. 初始化顺序

AppController::begin() 中的初始化顺序遵循以下原则（`AppController.cpp:7-82`）：

1. **Logger 最先** — 所有模块依赖日志
2. **ConfigService 在 DisplayManager 之前** — `displayManager_.setBrightness(configService_.getBrightness())`
3. **DisplayManager 在 LVGLPort 之前** — LVGL flush 回调需要 LCD 已初始化
4. **TouchManager 在 LVGLPort 之前** — LVGL touch 回调需要触摸已初始化
5. **LVGLPort 在 UIManager 之前** — HomeScreen 创建 LVGL 对象需要 lv_init 已完成
6. **UIManager 在各 Service 之前** — Service 初始化后通过 UIManager setter 更新 HomeScreen 文本
7. **各 Service 在对应 UI setter 之后** — 确保 LVGL label 对象已创建
8. **剩余占位 Service 最后** — 无严格依赖顺序

---

## 5. Update 顺序

AppController::update() 中的调度顺序（`AppController.cpp:84-106`）：

1. `displayManager_.update()` — 最先：确保显示帧缓冲就绪
2. `powerManager_.update()` — 电源状态（当前空）
3. `touchManager_.update()` — 读取最新触摸数据
4. `lvglPort_.update()` — **最关键**：`lv_timer_handler()` → LVGL 定时器 → 渲染 → flush 回调
5. `uiManager_.update()` — 当前页面更新（仅 Home）
6-15. 各 Service update() — 顺序无严格要求（Service 间无相互依赖）
16. 每 2000ms：`Logger::info("running...")`

**ConfigService 不参与 update() 循环** — 配置在 begin() 时加载一次即可。

---

## 6. 模块依赖关系

```
main.cpp
  └── AppController
        ├── Logger (横向工具层，被所有模块依赖)
        ├── BoardConfig (编译期常量，被所有模块 include)
        │
        ├── ConfigService ──── Preferences (NVS)
        │
        ├── DisplayManager ─── DisplayPanelDriver ─── ESP32DisplayPanelDriver ──┐
        ├── TouchManager ───── GT911TouchDriver ────────────────────────────────┤
        ├── LVGLPort ──────────────────────────────────────────────────────────┤
        │     └── (flush/touch 回调中) ────────────────────────────────────────┼── PanelContext ── ESP_Panel
        │                                                                       │
        ├── UIManager ── HomeScreen ── ScreenBase ── lvgl                       │
        │
        ├── PowerManager
        ├── TimeService
        ├── WiFiService ────── WiFi.h (Arduino)
        ├── BatteryService / WeatherService / SDCardService
        ├── AlbumService / MemoService / AIService
        └── WebServerService / OTAService
```

- 不存在循环依赖
- 依赖方向为严格单向树状结构
- 不存在接口抽象（纯虚基类）
- 不存在依赖注入容器

---

## 7. 数据流

当前不存在事件总线或消息队列。模块间通信方式：

| 方式 | 说明 | 示例 |
|------|------|------|
| **直接方法调用** | AppController 调用各模块 public 方法 | 最主要方式 |
| **Setter 注入（Push Model）** | AppController 将 Service 数据推送到 UIManager | `uiManager_.setHomeTimeText("--:--")` |
| **单例访问** | Driver 通过 PanelContext::getPanel() 获取 ESP_Panel | `PanelContext::getPanel().getLcd()` |
| **编译期常量共享** | 通过 `#include BoardConfig.h` | 引脚定义、屏幕尺寸 |

### 当前数据流路径

```
TimeService    ──(占位数据)──┐
WiFiService    ──(状态文本)──┤
BatteryService ──(占位数据)──┼── AppController ── UIManager ── HomeScreen
WeatherService ──(占位数据)──┤        (5 个 setHomeXxxText 调用)
                              └── LVGL label 更新
```

---

## 8. 关键设计决策

| 决策 | 说明 | ADR |
|------|------|-----|
| AppController 作为唯一协调器 | 所有模块通过 AppController 编排 | [ADR-0001](DECISIONS.md#adr-0001) |
| 轮询（Polling）调度 | 无 RTOS，单线程 loop 循环 | [ADR-0003](DECISIONS.md#adr-0003) |
| 门面模式隔离驱动 | DisplayPanelDriver 封装 ESP32DisplayPanelDriver | [DECISIONS.md](DECISIONS.md) |
| 值成员变量而非指针 | 所有模块作为 AppController 的值成员，生命周期统一 | [DECISIONS.md](DECISIONS.md) |
| 单例共享硬件 | PanelContext 持有全局唯一 ESP_Panel | [DECISIONS.md](DECISIONS.md) |
