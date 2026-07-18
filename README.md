# SmartDesktop

ESP32-S3 智能桌面摆件 — 5 寸触摸屏 + LVGL + WiFi + AI 交互。

---

## 项目目标

- 5 寸 IPS 触摸屏（800x480）展示时间、日期、天气
- WiFi 联网，手机 Web 配置页管理设备
- AI 聊天交互（后续接入 LLM API）
- 相册轮播（SD 卡读取）
- 备忘录显示与管理
- OTA 无线固件升级
- 低功耗桌面设备，长时间稳定运行

---

## 当前开发状态

| 项目 | 内容 |
|------|------|
| **Current Stage** | v0.1 — Project Recovery（文档体系建设） |
| **Current Module** | 文档体系建设 |
| **Next Module** | TimeService（NTP 时间同步） |

---

## 系统架构概览

```
AppController  →  统一编排所有模块的 begin() / update()
    ├── Manager   →  硬件资源管理（Display / Touch / UI / Power / LVGL）
    ├── Service   →  业务功能（Time / WiFi / Config / Battery / Weather / ...）
    ├── UI        →  LVGL 页面（ScreenBase → HomeScreen）
    ├── Driver    →  底层驱动适配（ST7262 RGB / GT911 Touch）
    └── Hardware  →  ESP_Panel（ESP32_Display_Panel 库）
```

一句话：**AppController** 持有所有 Manager 和 Service，在 `begin()` 中按依赖顺序初始化，在 `update()` 中每帧调度。

---

## 工程目录

```
AI_Desktop_Companion/
├── src/                    # 源码
│   ├── main.cpp            # 程序入口
│   └── modules/            # 21 个功能模块
├── include/                # 全局头文件
├── lib/                    # 私有库
├── data/                   # SPIFFS 数据
├── docs/                   # 项目文档
├── platformio.ini          # PlatformIO 配置
├── ESP_Panel_Conf.h        # 硬件配置（LCD / Touch / 背光）
├── lv_conf.h               # LVGL 配置
└── README.md               # 本文件
```

---

## 编译方式

| 项目 | 规格 |
|------|------|
| **芯片** | ESP32-S3-WROOM-1 (N8R8) |
| **框架** | Arduino |
| **构建** | PlatformIO |
| **UI** | LVGL v8.3.11 |
| **显示库** | ESP32_Display_Panel |

```bash
pio run                    # 编译
pio run --target upload    # 烧录
pio device monitor         # 串口监视
```

---

## 文档说明

完整文档位于 [docs/](docs/) 目录：

| 文档 | 用途 | 阅读对象 |
|------|------|----------|
| [PROJECT_RECOVERY.md](docs/PROJECT_RECOVERY.md) | 项目恢复指南 — AI 接管第一优先阅读 | AI / 新开发者 |
| [ARCHITECTURE.md](docs/ARCHITECTURE.md) | 系统架构（分层、生命周期、依赖、数据流） | 开发者 |
| [DEVELOPMENT_LOG.md](docs/DEVELOPMENT_LOG.md) | 开发日志（每个版本/模块的记录） | 所有人 |
| [ROADMAP.md](docs/ROADMAP.md) | 开发路线图（模块清单 + 完成状态） | 项目管理 |
| [INTERFACE.md](docs/INTERFACE.md) | 接口冻结记录 | 开发者 |
| [DEVELOPMENT_RULES.md](docs/DEVELOPMENT_RULES.md) | 开发规范（流程 / Review / 优先级） | 所有人 |
| [DECISIONS.md](docs/DECISIONS.md) | 架构决策记录（ADR） | 架构 / Tech Lead |
