#pragma once

#include "../display/DisplayDriver.h"
#include "../touch/TouchManager.h"
#include "../display/LVGLAdapter.h"
#include "../ui/UIDataProvider.h"
#include "../ui/UIEventManager.h"
#include "../ui/UIManager.h"
#include "../ui/UIActionDispatcher.h"
#include "../time/TimeService.h"
#include "../power/PowerManager.h"
#include "../wifi/WiFiService.h"
#include "../config/ConfigService.h"
#include "../settings/SettingsService.h"
#include "../battery/BatteryService.h"
#include "../weather/WeatherService.h"
#include "../sdcard/SDCardService.h"
#include "../album/AlbumService.h"
#include "../memo/MemoService.h"
#include "../ai/AIService.h"
#include "../web_server/WebServerService.h"
#include "../ota/OTAService.h"
#include "../storage/StorageService.h"
#include "../system_status/SystemStatusManager.h"

/// @brief 应用控制器 — 统一管理启动流程与主循环调度。
///
/// 各类 Service 后续都将由 AppController 统一调度。

class AppController {
public:
    /// @brief 初始化应用（按顺序初始化各子模块）。
    void begin();

    /// @brief 主循环更新（每帧调用，调度各子模块 update）。
    void update();

private:
    PowerManager powerManager_;
    DisplayDriver displayDriver_;
    TouchManager touchManager_;
    LVGLAdapter lvglAdapter_;
    UIEventManager uiEventManager_;
    UIManager uiManager_;
    UIActionDispatcher uiActionDispatcher_;
    TimeService timeService_;
    WiFiService wifiService_;
    ConfigService configService_;
    SettingsService settingsService_;
    BatteryService batteryService_;
    WeatherService weatherService_;
    SDCardService sdCardService_;
    AlbumService albumService_;
    MemoService memoService_;
    AIService aiService_;
    WebServerService webServerService_;
    OTAService otaService_;
    StorageService storageService_;
    SystemStatusManager systemStatusManager_;
    UIDataProvider uiDataProvider_;
};
