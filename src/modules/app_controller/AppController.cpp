#include "AppController.h"
#include "../logger/Logger.h"
#include "../board_config/BoardConfig.h"
#include <Arduino.h>

void AppController::begin() {
    Logger::begin(BoardConfig::SERIAL_BAUD_RATE);
    Logger::info(String("Project: ") + BoardConfig::PROJECT_NAME);
    Logger::info(String("Screen: ") + BoardConfig::SCREEN_WIDTH + "x" + BoardConfig::SCREEN_HEIGHT);
    Logger::info("AppController started");

    // ---- Storage Layer ----
    if (storageService_.begin()) {
        Logger::info("StorageService test passed");
    }

    // ---- Config (depends on Storage via NVS) ----
    if (configService_.begin(&storageService_)) {
        Logger::info("ConfigService test passed");
        Logger::info("ConfigService ready");
    }

    // ---- Settings (depends on Config) ----
    if (settingsService_.begin(&configService_)) {
        Logger::info("SettingsService test passed");
        settingsService_.setBrightness(50);
        Logger::info(String("Settings brightness test: ") + String(settingsService_.getBrightness()));
        Logger::info("SettingsService ready");
    }

    // ---- Core Services ----
    if (powerManager_.begin()) {
        Logger::info("PowerManager test passed");
        Logger::info("PowerManager ready");
    }

    if (wifiService_.begin(&configService_)) {
        Logger::info("WiFiService test passed");
        Logger::info("WiFiService ready");
    }
    if (configService_.hasWifiConfig()) {
        wifiService_.connect();
        Logger::info(String("WiFi connecting to: ") + configService_.getWifiSSID());
    }

    if (batteryService_.begin()) {
        Logger::info("BatteryService test passed");
        Logger::info("BatteryService ready");
    }

    if (timeService_.begin()) {
        Logger::info("TimeService test passed");
        Logger::info("TimeService ready");
    }
    String timeStr = timeService_.getTimeString();
    // TODO: Re-enable UI data binding when UIManager supports screens

    if (weatherService_.begin()) {
        Logger::info("WeatherService test passed");
        Logger::info("WeatherService ready");
    }

    if (sdCardService_.begin()) {
        Logger::info("SDCardService test passed");
        Logger::info("SDCardService ready");
    }

    if (albumService_.begin(&sdCardService_)) {
        Logger::info("AlbumService test passed");
        Logger::info("AlbumService ready");
    }
    albumService_.scanImages();
    Logger::info(String("AlbumService image count: ") + String(albumService_.getImageCount()));

    if (memoService_.begin(&storageService_)) {
        Logger::info("MemoService test passed");
        Logger::info("MemoService ready");
    }
    memoService_.addMemo("Test", "Hello");
    Logger::info(String("MemoService count: ") + String(memoService_.getMemoCount()));
    if (memoService_.getMemoCount() == 1) {
        Logger::info(String("MemoService title: ") + memoService_.getMemoTitle(0));
        memoService_.removeMemo(0);
        Logger::info(String("MemoService after remove count: ") + String(memoService_.getMemoCount()));
    }

    if (aiService_.begin()) {
        Logger::info("AIService test passed");
    }
    if (aiService_.request("test")) {
        Logger::info(String("AIService test passed: ") + aiService_.getLastResponse());
    }
    Logger::info("AIService ready");

    if (webServerService_.begin()) {
        Logger::info("WebServerService test passed");
    }
    if (webServerService_.start()) {
        Logger::info(String("WebServerService test passed: ") + webServerService_.getStatusJson());
    }
    Logger::info("WebServerService ready");

    if (otaService_.begin()) {
        Logger::info("OTAService test passed");
    }
    if (otaService_.startUpdate()) {
        Logger::info(String("OTAService test passed: progress=") + String(otaService_.getProgress()));
        otaService_.stopUpdate();
    }
    Logger::info("OTAService ready");

    // ---- System Status ----
    systemStatusManager_.begin();
    systemStatusManager_.setWifiStatus(wifiService_.isConnected());
    systemStatusManager_.setBatteryLevel(batteryService_.getPercentage());
    systemStatusManager_.setCharging(batteryService_.isCharging());
    systemStatusManager_.setTime(timeStr);
    systemStatusManager_.setWebServerStatus(webServerService_.isRunning());
    {
        Logger::info(String("SystemStatus: WiFi=") + (systemStatusManager_.isWifiConnected() ? "ON" : "OFF")
            + " Battery=" + String(systemStatusManager_.getBatteryLevel()) + "%"
            + " Time=" + systemStatusManager_.getTime()
            + " WebServer=" + (webServerService_.isRunning() ? "ON" : "OFF"));
    }

    // ---- Notification Service ----
    notificationService_.begin();
    notificationService_.notify("Test notification");
    Logger::info(String("Notification test: ") + notificationService_.getMessage());
    notificationService_.clear();
    Logger::info("NotificationService ready");

    // ---- UI Data Provider ----
    if (uiDataProvider_.begin(&systemStatusManager_)) {
        Logger::info("UIDataProvider test passed");
        Logger::info(String("UIDataProvider: time=") + uiDataProvider_.getTime()
            + " battery=" + String(uiDataProvider_.getBatteryLevel()) + "%"
            + " wifi=" + (uiDataProvider_.isWifiConnected() ? "ON" : "OFF"));
    }

    // ---- Display & Touch ----
    if (displayDriver_.begin()) {
        Logger::info("DisplayDriver test passed");
    }

    if (touchManager_.begin()) {
        Logger::info("TouchManager test passed");
        Logger::info("TouchManager ready");
    }

    // ---- LVGL ----
    if (lvglAdapter_.begin()) {
        Logger::info("LVGLAdapter test passed");
    }

    // ---- UI Event Manager (connects touch to screen switching) ----
    if (uiEventManager_.begin(&touchManager_, &uiManager_)) {
        Logger::info("UIEventManager test passed");
        Logger::info("UIEventManager ready");
    }

    // ---- UI Manager (after LVGL is ready) ----
    if (uiManager_.begin(&uiDataProvider_, &settingsService_)) {
        Logger::info("UIManager test passed");
    }

    // ---- UI Action Dispatcher ----
    if (uiActionDispatcher_.begin(uiManager_.getActionManager(), &uiManager_)) {
        Logger::info("UIActionDispatcher test passed");
        Logger::info("UIActionDispatcher ready");
    }

    // Test menu switching
    uiManager_.switchScreen(UIManager::ScreenType::MENU);
    uiManager_.switchScreen(UIManager::ScreenType::HOME);
    Logger::info("Menu switch test passed");
    Logger::info("Touch event test passed");

    // Test UIActionManager
    UIActionManager* actionMgr = uiManager_.getActionManager();
    if (actionMgr != nullptr) {
        Logger::info("UIActionManager initialized");
        actionMgr->setAction(UIAction::OPEN_ABOUT);
        Logger::info(String("Menu action test: ") + String(static_cast<int>(actionMgr->getAction())));
        actionMgr->clearAction();
        Logger::info("Menu item action test passed");
    }
}

void AppController::update() {
    // ---- Services (data producers) ----
    settingsService_.update();
    wifiService_.update();
    batteryService_.update();
    timeService_.update();
    weatherService_.update();
    sdCardService_.update();
    albumService_.update();
    memoService_.update();
    aiService_.update();
    webServerService_.update();
    otaService_.update();
    powerManager_.update();

    // ---- System Status (data aggregation) ----
    systemStatusManager_.setWifiStatus(wifiService_.isConnected());
    systemStatusManager_.setBatteryLevel(batteryService_.getPercentage());
    systemStatusManager_.setCharging(batteryService_.isCharging());
    systemStatusManager_.setTime(timeService_.getTimeString());
    if (weatherService_.isWeatherValid()) {
        systemStatusManager_.setWeather(weatherService_.getWeather(),
                                        weatherService_.getTemperature());
    }
    systemStatusManager_.setWebServerStatus(webServerService_.isRunning());
    notificationService_.update();

    // ---- UI Data (formatting) ----
    uiDataProvider_.update();

    // ---- Touch Input ----
    touchManager_.update();

    // ---- UI Events (touch → screen switching) ----
    uiEventManager_.update();

    // ---- UI Rendering (label refresh + LVGL render) ----
    uiManager_.update();

    // ---- Action Dispatch (process queued UI actions) ----
    uiActionDispatcher_.update();

    lvglAdapter_.update();

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint >= 2000) {
        lastPrint = millis();
        Logger::info(String("SystemStatus: WiFi=") + (systemStatusManager_.isWifiConnected() ? "ON" : "OFF")
            + " Battery=" + String(systemStatusManager_.getBatteryLevel()) + "%"
            + " Time=" + systemStatusManager_.getTime()
            + " WebServer=" + (webServerService_.isRunning() ? "ON" : "OFF"));
    }
}
