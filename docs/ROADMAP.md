# Roadmap — 开发路线图

> 模块清单 + 完成状态。详细架构见 [ARCHITECTURE.md](ARCHITECTURE.md)。

---

## 图例

| 标记 | 含义 |
|------|------|
| ✅ | 已完成 |
| 🔵 | 当前开发 |
| ⏳ | 未开始 |

---

## 开发路线

### 第一阶段：基础设施 + 驱动

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 01 | Logger | ✅ | Serial 三级日志 |
| 02 | BoardConfig | ✅ | 板级常量（引脚/时序/参数） |
| 03 | PanelContext | ✅ | ESP_Panel 单例 |

### 第二阶段：显示 + 触摸驱动

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 04 | ESP32DisplayPanelDriver | ✅ | ST7262 RGB 屏底层驱动 |
| 05 | DisplayPanelDriver | ✅ | 显示驱动门面层 |
| 06 | GT911TouchDriver | ✅ | GT911 触摸底层驱动 |

### 第三阶段：Manager 层

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 07 | DisplayManager | ✅ | 显示管理（背光/面板状态） |
| 08 | TouchManager | ✅ | 触摸管理（状态/坐标缓存） |
| 09 | LVGLPort | ✅ | LVGL 适配（缓冲/回调/timer） |

### 第四阶段：UI 基础

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 10 | ScreenBase | ✅ | 页面抽象基类 |
| 11 | HomeScreen | ✅ | 主页面 LVGL UI（6 label） |
| 12 | UIManager | ✅ | 页面切换 + 数据转发 |

### 第五阶段：配置 + 电源

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 13 | ConfigService | ✅ | NVS 持久化 |
| 14 | PowerManager | ✅ | 电源管理状态机 |

### 第六阶段：应用控制器 + WiFi

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 15 | WiFiService | ✅ | WiFi STA / connect / scan |
| 16 | AppController | ✅ | 16 模块统一编排 |

### 第七阶段：核心 Service（逐模块开发）

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 17 | TimeService | 🔵 | NTP 时间同步 **← Next Module** |
| 18 | BatteryService | ⏳ | ADC 电量检测 + 充电状态 |
| 19 | WeatherService | ⏳ | 天气 API + JSON 解析 |
| 20 | SDCardService | ⏳ | SPI SD 卡挂载 + FAT 文件系统 |

### 第八阶段：数据 Service

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 21 | AlbumService | ⏳ | 图片扫描 + 轮播 |
| 22 | MemoService | ⏳ | JSON 文件持久化 |
| 23 | AIService | ⏳ | AI API 调用 + 对话管理 |

### 第九阶段：网络 Service

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 24 | WebServerService | ⏳ | HTTP Server + 配置页 + 文件上传 |
| 25 | OTAService | ⏳ | 无线固件升级 |

### 第十阶段：UI 扩展

| # | 模块 | 状态 | 说明 |
|---|------|------|------|
| 26 | AlbumScreen | ⏳ | 图片浏览页面 |
| 27 | MemoScreen | ⏳ | 备忘录显示页面 |
| 28 | ChatScreen | ⏳ | AI 对话页面 |

### 第十一阶段：集成 + 发布

| # | 里程碑 | 状态 | 说明 |
|---|------|------|------|
| 29 | System Integration | ⏳ | 全模块集成联调 |
| 30 | Optimization | ⏳ | 性能 / 内存 / 稳定性优化 |
| 31 | Release v1.0 | ⏳ | 稳定版发布 |

---

## 开发规则

1. **严格按顺序开发**：当前模块未完成之前，禁止开发下一模块。
2. **禁止跨模块修改**：开发某模块时，禁止顺手修改其他模块（除非明确要求）。
3. **开发流程**：`.h → Review → .cpp → Review → Integration Test → Review`。
4. 详见 [DEVELOPMENT_RULES.md](DEVELOPMENT_RULES.md)。
