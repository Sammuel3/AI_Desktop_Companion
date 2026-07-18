# Interface — 接口冻结记录

> 只有 `.h` 审核通过后，才能更新本文件。

---

## 图例

| 状态 | 含义 |
|------|------|
| 🔒 已冻结 | 接口稳定，禁止随意修改 |
| 🔓 未冻结 | 接口仍在开发中，可以修改 |

---

## 接口冻结清单

### Manager 层

| 模块 | 文件 | 状态 | 冻结日期 | 说明 |
|------|------|------|----------|------|
| DisplayManager | `src/modules/display_manager/DisplayManager.h` | 🔒 已冻结 | — | `begin()/update()/setBrightness()/getBrightness()/isInitialized()/fillScreen()` |
| TouchManager | `src/modules/touch_manager/TouchManager.h` | 🔒 已冻结 | — | `begin()/update()/isTouched()/getX()/getY()/isInitialized()` |
| LVGLPort | `src/modules/lvgl_port/LVGLPort.h` | 🔒 已冻结 | — | `begin()/update()/isInitialized()/isLvglEnabled()/getScreenWidth()/getScreenHeight()` |
| UIManager | `src/modules/ui_manager/UIManager.h` | 🔒 已冻结 | — | `begin()/update()/showHome()/showAlbum()/showMemo()/showChat()/getCurrentScreen()/isInitialized()` + 5 个 setHomeXxxText |
| PowerManager | `src/modules/power_manager/PowerManager.h` | 🔒 已冻结 | — | `begin()/update()/isScreenOn()/isSleepRequested()/getStatusText()/notifyUserActivity()/requestSleep()/cancelSleepRequest()/setScreenOn()` |

### Service 层

| 模块 | 文件 | 状态 | 冻结日期 | 说明 |
|------|------|------|----------|------|
| ConfigService | `src/modules/config_service/ConfigService.h` | 🔒 已冻结 | — | `begin()/load()/save()/setWifiSsid()/getWifiSsid()/setWifiPassword()/getWifiPassword()/hasWifiConfig()/clearWifiConfig()/setDeviceName()/getDeviceName()/setBrightness()/getBrightness()` |
| WiFiService | `src/modules/wifi_service/WiFiService.h` | 🔒 已冻结 | — | `begin()/update()/connect()/scanNetworks()/getNetworkCount()/getNetworkInfo()/clearScanResults()/isConnected()/getStatusText()/getLocalIpString()/getSsid()` |
| TimeService | `src/modules/time_service/TimeService.h` | 🔓 未冻结 | — | 当前使用占位时间，NTP 实现时将扩展接口 |
| BatteryService | `src/modules/battery_service/BatteryService.h` | 🔓 未冻结 | — | 当前占位，ADC 实现时将可能调整接口 |
| WeatherService | `src/modules/weather_service/WeatherService.h` | 🔓 未冻结 | — | 当前占位，API 实现时将可能调整接口 |
| SDCardService | `src/modules/sdcard_service/SDCardService.h` | 🔓 未冻结 | — | 当前占位 |
| AlbumService | `src/modules/album_service/AlbumService.h` | 🔓 未冻结 | — | 当前占位 |
| MemoService | `src/modules/memo_service/MemoService.h` | 🔓 未冻结 | — | 当前占位 |
| AIService | `src/modules/ai_service/AIService.h` | 🔓 未冻结 | — | 当前占位 |
| WebServerService | `src/modules/web_server_service/WebServerService.h` | 🔓 未冻结 | — | 当前占位 |
| OTAService | `src/modules/ota_service/OTAService.h` | 🔓 未冻结 | — | 当前占位 |

### UI 层

| 模块 | 文件 | 状态 | 冻结日期 | 说明 |
|------|------|------|----------|------|
| ScreenBase | `src/modules/screen_base/ScreenBase.h` | 🔒 已冻结 | — | `begin()/show()/hide()/update()/getName()/isVisible()` — 抽象接口 |
| HomeScreen | `src/modules/home_screen/HomeScreen.h` | 🔒 已冻结 | — | 继承 ScreenBase + 5 个 setXxxText |

### Application 层

| 模块 | 文件 | 状态 | 冻结日期 | 说明 |
|------|------|------|----------|------|
| AppController | `src/modules/app_controller/AppController.h` | 🔒 已冻结 | — | `begin()/update()` — 顶层协调器 |

### Driver 层

| 模块 | 文件 | 状态 | 冻结日期 | 说明 |
|------|------|------|----------|------|
| DisplayPanelDriver | `src/modules/display_panel_driver/DisplayPanelDriver.h` | 🔒 已冻结 | — | `begin()/update()/isInitialized()/getWidth()/getHeight()/fillScreen()` |
| ESP32DisplayPanelDriver | `src/modules/esp32_display_panel_driver/ESP32DisplayPanelDriver.h` | 🔒 已冻结 | — | 底层驱动接口 |
| GT911TouchDriver | `src/modules/gt911_touch_driver/GT911TouchDriver.h` | 🔒 已冻结 | — | `begin()/update()/isInitialized()/isTouched()/getX()/getY()` |

### Utility 层

| 模块 | 文件 | 状态 | 冻结日期 | 说明 |
|------|------|------|----------|------|
| Logger | `src/modules/logger/Logger.h` | 🔒 已冻结 | — | `begin()/info()/warn()/error()` — 全静态方法 |
| BoardConfig | `src/modules/board_config/BoardConfig.h` | 🔒 已冻结 | — | 命名空间 + constexpr 常量 |
| PanelContext | `src/modules/panel_context/PanelContext.h` | 🔒 已冻结 | — | `getPanel()` — 单例 |

---

## 冻结规则

1. `.h` 审核通过后默认冻结，禁止随意修改。
2. 只有以下情况允许修改已冻结接口：
   - Bug 修复（接口行为与文档不符）
   - 影响后续模块开发（接口不足以支持新功能）
   - 严重性能问题（接口设计导致无法接受的性能损耗）
3. 修改已冻结接口需要：
   - 更新本文件
   - 更新 DEVELOPMENT_LOG.md
   - 更新受影响模块的 .cpp 实现
   - 通过 Integration Test

详见 [DEVELOPMENT_RULES.md](DEVELOPMENT_RULES.md) — 接口冻结规则。
