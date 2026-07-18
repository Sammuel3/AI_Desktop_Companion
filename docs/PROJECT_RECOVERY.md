# Project Recovery — AI 接管指南

> **第一优先阅读。** 任何 AI 或新开发者接管项目时，本文档提供完整项目恢复所需的所有信息。

---

## 1. 项目概况

| 项目 | 内容 |
|------|------|
| **项目名称** | SmartDesktop |
| **项目类型** | ESP32-S3 智能桌面摆件（嵌入式固件） |
| **芯片** | ESP32-S3-WROOM-1 (N8R8: 8MB Flash / 8MB PSRAM) |
| **实测 Flash** | 16MB（当前使用 `default_8MB.csv`，8MB 可用） |
| **屏幕** | JC8048W550C（5 寸 IPS，800x480，ST7262 RGB + GT911 触摸） |
| **框架** | Arduino + PlatformIO |
| **UI** | LVGL v8.3.11 |
| **显示驱动** | ESP32_Display_Panel (lzw655) |
| **语言** | C++ |
| **构建系统** | PlatformIO (platform = espressif32, board = freenove_esp32_s3_wroom) |

---

## 2. 开发目标

1. 5 寸触摸屏展示时间、日期、天气等日常信息
2. WiFi 联网，手机 Web 配置页管理设备
3. AI 聊天交互（接入 LLM API）
4. 相册轮播（SD 卡读取图片）
5. 备忘录显示与管理
6. OTA 无线固件升级
7. 低功耗桌面设备，长时间稳定运行

---

## 3. 当前开发状态

| 项目 | 内容 |
|------|------|
| **Current Stage** | v0.1 — Project Recovery + 文档体系建设 |
| **Current Module** | 文档体系建设 |
| **Next Module** | TimeService（NTP 时间同步） |

---

## 4. 当前版本

| 项目 | 内容 |
|------|------|
| **版本号** | v0.1 |
| **版本名称** | Project Recovery |
| **日期** | 2026-07-18 |
| **版本控制** | 无法从当前源码确定（项目目录下未检测到 .git 文件夹） |

---

## 5. 已完成模块

以下模块已通过真实硬件验证，**可编译、可烧录、可运行**：

| # | 模块 | 文件位置 | 完成度 | 说明 |
|---|------|----------|--------|------|
| 1 | Logger | `src/modules/logger/` | 100% | Serial 三级日志（INFO/WARN/ERROR） |
| 2 | BoardConfig | `src/modules/board_config/` | 95% | 全部引脚/时序定义（命名空间 + constexpr） |
| 3 | PanelContext | `src/modules/panel_context/` | 100% | ESP_Panel 全局单例 |
| 4 | ESP32DisplayPanelDriver | `src/modules/esp32_display_panel_driver/` | 90% | ST7262 RGB 屏真实驱动 + PSRAM fillScreen |
| 5 | DisplayPanelDriver | `src/modules/display_panel_driver/` | 100% | 门面层，委托 ESP32DisplayPanelDriver |
| 6 | GT911TouchDriver | `src/modules/gt911_touch_driver/` | 90% | GT911 触摸驱动（readData + getPoint） |
| 7 | DisplayManager | `src/modules/display_manager/` | 95% | 背光亮度管理 + 面板状态 + 屏幕填充 |
| 8 | TouchManager | `src/modules/touch_manager/` | 95% | 触摸状态缓存 + 坐标管理 |
| 9 | LVGLPort | `src/modules/lvgl_port/` | 95% | lv_init + PSRAM 双缓冲 + flush/touch 回调 |
| 10 | ScreenBase | `src/modules/screen_base/` | 100% | 页面抽象基类（begin/show/hide/update/getName） |
| 11 | HomeScreen | `src/modules/home_screen/` | 85% | LVGL 深色主题 UI（6 个 label） |
| 12 | UIManager | `src/modules/ui_manager/` | 70% | 页面切换 + HomeScreen 数据转发 |
| 13 | PowerManager | `src/modules/power_manager/` | 80% | 屏幕开关 / 休眠请求 / 用户活动跟踪 |
| 14 | WiFiService | `src/modules/wifi_service/` | 85% | STA 模式 + connect(10s超时) + scanNetworks |
| 15 | ConfigService | `src/modules/config_service/` | 90% | Preferences(NVS) 持久化（WiFi/设备名/亮度） |
| 16 | AppController | `src/modules/app_controller/` | 90% | 16 模块统一编排（begin + update） |

---

## 6. 当前开发中模块

| # | 模块 | 完成度 | 状态 |
|---|------|--------|------|
| 17 | TimeService | 20% | 占位 `--:--`，无 NTP |
| 18 | MemoService | 50% | 内存存储（setMemo/clearMemo），无持久化 |
| 19 | AIService | 30% | 占位回复 "AI placeholder reply"，无 API |

---

## 7. 未完成模块（仅有 begin/update 占位）

| # | 模块 | 完成度 |
|---|------|--------|
| 20 | BatteryService | 15%（占位 0%） |
| 21 | WeatherService | 10%（占位 `--`） |
| 22 | SDCardService | 10%（占位 未挂载） |
| 23 | AlbumService | 30%（nextImage/previousImage 逻辑已实现，无图片数据） |
| 24 | WebServerService | 10%（start/stop 仅设标志位） |
| 25 | OTAService | 10%（setEnabled 仅设标志位） |

---

## 8. 系统启动流程

```
[ESP32-S3 上电]
  → Bootloader (ROM)
  → Arduino main() 框架初始化（PSRAM 8MB, Flash 16MB, SPI/I2C/GPIO）
  → 静态初始化：构造全局 AppController app（16 个子模块值成员构造）
  → setup() → app.begin()
       1. Logger::begin(115200)
       2-4. 项目信息日志
       5. configService_.begin()          → NVS 加载配置
       6. displayManager_.begin()         → ST7262 RGB 屏初始化 + fillScreen(0,0,0)
       7. displayManager_.setBrightness(config.getBrightness())
       8. powerManager_.begin()
       9. touchManager_.begin()           → GT911 触摸初始化
      10. lvglPort_.begin()              → lv_init + PSRAM 双缓冲 + flush/touch 回调
      11. uiManager_.begin()             → HomeScreen LVGL UI 创建 + showHome()
      12-25. UI setter 占位文本 + 各 Service begin()
      26. otaService_.begin()
  → loop() → app.update()
       1. displayManager_.update()
       2. powerManager_.update()
       3. touchManager_.update()
       4. lvglPort_.update()             → lv_timer_handler() → LVGL 渲染
       5. uiManager_.update()
       6-15. 各 Service update()（10 个，大部分为空）
      16. 每 2000ms: Logger::info("running...")
  → (无限循环)
```

---

## 9. AppController 职责

- **持有**：16 个 Manager/Service 的值类型成员变量（AppController.h:33-48）
- **begin()**：按依赖顺序初始化所有模块（AppController.cpp:7-82）
- **update()**：按固定顺序调度所有模块的 update()（AppController.cpp:84-106）
- **数据流**：Service 初始化后通过 UIManager setter 推送数据到 HomeScreen

---

## 10. 模块依赖关系

```
main.cpp → AppController → Manager/Service → Driver → PanelContext → ESP_Panel
```

- Logger 和 BoardConfig 是横向工具层，被所有模块依赖
- 不存在循环依赖
- 不存在事件总线或消息队列
- 模块间通信通过 AppController 直接方法调用

详见 [ARCHITECTURE.md](ARCHITECTURE.md)。

---

## 11. 当前存在的问题

| # | 问题 | 位置 | 严重程度 |
|---|------|------|----------|
| 1 | 16MB Flash 分区表 boot loop，当前仅用 8MB | `BoardConfig.h:113` | 中 |
| 2 | setBrightness() 仅存储变量，无 PWM 硬件控制 | `DisplayManager.cpp:22-27` | 低 |
| 3 | PowerManager::update() 为空，无空闲超时检测 | `PowerManager.cpp:14-16` | 低 |
| 4 | 10 个 Service 的 update() 为空实现 | 各 Service .cpp | 低（开发中正常状态） |
| 5 | HomeScreen 使用 const char* 存储文本，不复制字符串 | `HomeScreen.h:31-34` | 低（当前用字面量安全） |
| 6 | app.begin() 返回值未检查 | `main.cpp:7` | 低 |
| 7 | begin() 失败后后续模块仍继续初始化（级联风险） | `AppController.cpp:13-81` | 低 |
| 8 | 无 ESP32 看门狗喂狗 | `main.cpp` | 低 |

---

## 12. TODO 统计

| 类型 | 数量 | 位置 |
|------|------|------|
| TODO 注释 | 1 | `BoardConfig.h:113` |
| 空 update() 函数 | 10 | TimeService / BatteryService / WeatherService / SDCardService / AlbumService / MemoService / AIService / WebServerService / OTAService / PowerManager |
| 占位数据 | 3 | TimeService (`--:--`), AIService (`AI placeholder reply`), WeatherService (`--`) |
| 未实现 Screen 类 | 3 | AlbumScreen / MemoScreen / ChatScreen |

---

## 13. 下一开发模块

### TimeService — NTP 时间同步

**推荐原因：**

1. 用户可见价值最高 — HomeScreen 从 `--:--` 变为正确时间
2. 依赖 WiFiService 已就绪
3. 开发范围可控 — 集中在 `TimeService.cpp` + 少量 `AppController.cpp` 集成
4. 不影响其他模块
5. 建立 WiFi → Service 数据流模式，供 WeatherService、AIService 复用

**开发要点：**

- 调用 `configTime()` 配置 NTP（`pool.ntp.org`）
- 在 WiFi 连接后自动同步
- `getTimeString()` → `HH:MM`，`getDateString()` → `YYYY/MM/DD`
- `isTimeValid()` 在首次 NTP 同步成功后返回 true
- AppController 中：WiFi 连接成功后触发 NTP 同步

---

## 14. 恢复建议

1. **先读文档**：按顺序阅读 `docs/` 下的所有文档
2. **理解架构**：重点阅读 [ARCHITECTURE.md](ARCHITECTURE.md)
3. **编译验证**：`pio run` 确认项目可编译
4. **烧录验证**：`pio run --target upload` 确认硬件可用
5. **串口确认**：`pio device monitor` 验证启动日志
6. **开发 TimeService**：按照 [ROADMAP.md](ROADMAP.md) 和 [DEVELOPMENT_RULES.md](DEVELOPMENT_RULES.md) 的要求进行
7. **不可修改**：Logger / BoardConfig / PanelContext / ScreenBase / ConfigService 接口已冻结（详见 [INTERFACE.md](INTERFACE.md)）
