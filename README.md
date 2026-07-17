# SmartDesktop

ESP32-S3 智能桌面摆件项目。

## 当前阶段

最小正式工程框架。项目处于初始化阶段，仅包含可编译、可烧录的最小骨架。

## 硬件平台

- **主控**: ESP32-S3-WROOM-1 (16MB Flash, 8MB PSRAM)
- **屏幕**: JC8048W550C / JC8048W550 (5寸 IPS, 800x480, 电容触摸)
- **框架**: Arduino (PlatformIO)

## 当前状态

当前**不包含**以下功能：
- 屏幕显示 / 触摸驱动
- WiFi / 蓝牙
- AI / 语音
- 相册 / WebServer / OTA
- LVGL 或其他 UI 框架

## 后续计划

后续将逐步添加：

| 层次 | 模块 |
|------|------|
| 应用层 | AppController |
| 配置层 | BoardConfig |
| 基础设施层 | Logger |
| 硬件抽象层 | DisplayManager, TouchManager |
| UI 层 | UIManager |
| 业务层 | 各业务 Service |

## 构建与烧录

```bash
# 编译
pio run

# 烧录
pio run --target upload

# 串口监视
pio device monitor
```
