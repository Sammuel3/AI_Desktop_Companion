# Development Log — 开发日志

> 每个版本 / 每个模块完成后的开发记录。

---

## v0.1 — Project Recovery + 文档体系建设

| 项目 | 内容 |
|------|------|
| **日期** | 2026-07-18 |
| **版本** | v0.1 |
| **类型** | 项目恢复 |

### 完成内容

1. **项目恢复**：从旧版"最小骨架工程"恢复至完整的 16 模块框架，可编译、可烧录、可在真实硬件上运行。
2. **硬件验证**：
   - ST7262 RGB 屏（800x480）驱动正常
   - GT911 触摸驱动正常
   - PSRAM 8MB 可用（用于 LVGL 双缓冲）
3. **LVGL 集成**：PSRAM 双缓冲（800x40x2）、display flush 回调、touch read 回调、lv_timer_handler 调度。
4. **HomeScreen**：LVGL 深色主题 UI（6 个 label：标题 / 时间 / 日期 / WiFi / 电池 / 天气）。
5. **WiFi 功能**：STA 模式 + connect（10s 超时）+ scanNetworks。
6. **ConfigService**：Preferences(NVS) 持久化（WiFi 配置 / 设备名 / 亮度）。
7. **16 模块 AppController**：统一 begin() 和 update() 编排。
8. **文档体系**：建立 `docs/` 目录，包含 7 份项目文档。

### 模块状态

| 状态 | 数量 | 模块 |
|------|------|------|
| 已完成 | 16 | Logger / BoardConfig / PanelContext / ESP32DisplayPanelDriver / DisplayPanelDriver / GT911TouchDriver / DisplayManager / TouchManager / LVGLPort / ScreenBase / HomeScreen / UIManager / PowerManager / WiFiService / ConfigService / AppController |
| 开发中 | 3 | TimeService / MemoService / AIService |
| 未开始 | 6 | BatteryService / WeatherService / SDCardService / AlbumService / WebServerService / OTAService |
| 未创建 | 3 | AlbumScreen / MemoScreen / ChatScreen |

### 审核结果

- 编译：通过（`pio run` 成功）
- 烧录：通过（`pio run --target upload` 成功）
- 串口输出：`AppController started` → 全部 16 个 `XXX test passed` → 每 2s `running...`
- HomeScreen：深色背景（0x101820）+ 6 个白色/灰色 label 正常显示

---

## 日志格式说明

后续每完成一个模块，按以下格式追加：

```
## [模块名称] — v[版本号]

| 项目 | 内容 |
|------|------|
| **日期** | YYYY-MM-DD |
| **版本** | vX.Y |
| **模块** | [模块名称] |

### 修改内容
- [修改项 1]
- [修改项 2]

### 审核结果
- 编译：[通过/失败]
- 烧录：[通过/失败]
- 测试结果：[描述]
```
