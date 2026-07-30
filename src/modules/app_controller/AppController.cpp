#include "AppController.h"
#include "../logger/Logger.h"
#include "../board_config/BoardConfig.h"
#include "../screen_base/ScreenBase.h"
#include <Arduino.h>

void AppController::begin() {
    Logger::begin(BoardConfig::SERIAL_BAUD_RATE);
    Logger::info(String("Project: ") + BoardConfig::PROJECT_NAME);
    Logger::info(String("Screen: ") + BoardConfig::SCREEN_WIDTH + "x" + BoardConfig::SCREEN_HEIGHT);
    Logger::info("AppController started");

    if (configService_.begin()) {
        Logger::info("ConfigService test passed");
    }

    if (displayManager_.begin()) {
        Logger::info("DisplayManager test passed");
    }
    displayManager_.setBrightness(configService_.getBrightness());

    if (powerManager_.begin()) {
        Logger::info("PowerManager test passed");
    }

    if (touchManager_.begin()) {
        Logger::info("TouchManager test passed");
    }

    if (lvglPort_.begin()) {
        Logger::info("LVGLPort test passed");
    }

    if (uiManager_.begin()) {
        Logger::info("UIManager test passed");
    }

    if (timeService_.begin()) {
        Logger::info("TimeService test passed");
    }
    // TODO: 临时测试代码 — 下一阶段（WiFiService / NTP 开发前）移除
    timeService_.refresh("14:30", "2026/07/18");
    String timeStr = timeService_.getTimeString();
    String dateStr = timeService_.getDateString();
    uiManager_.setHomeTimeText(timeStr.c_str());
    uiManager_.setHomeDateText(dateStr.c_str());

    if (wifiService_.begin()) {
        Logger::info("WiFiService test passed");
    }
    if (configService_.hasWifiConfig()) {
        wifiService_.connect(configService_.getWifiSsid(), configService_.getWifiPassword());
        Logger::info(String("WiFi connecting to: ") + configService_.getWifiSsid());
    }
    {
        String wifiText = wifiService_.isConnected()
            ? String("WiFi: ") + wifiService_.getSSID()
            : "WiFi: Disconnected";
        uiManager_.setHomeWifiText(wifiText.c_str());
    }

    if (batteryService_.begin()) {
        Logger::info("BatteryService test passed");
    }
    {
        String batteryText = String("Battery: ") + batteryService_.getPercentage() + "%";
        uiManager_.setHomeBatteryText(batteryText.c_str());
    }

    if (weatherService_.begin()) {
        Logger::info("WeatherService test passed");
    }
    {
        String weatherText = weatherService_.isWeatherValid()
            ? String(weatherService_.getWeather()) + " " + weatherService_.getTemperature() + "C"
            : "Weather: --";
        uiManager_.setHomeWeatherText(weatherText.c_str());
    }

    if (sdCardService_.begin()) {
        Logger::info("SDCardService test passed");
    }

    if (albumService_.begin()) {
        Logger::info("AlbumService test passed");
    }

    if (memoService_.begin()) {
        Logger::info("MemoService test passed");
    }
    memoService_.setMemo("Test Memo");
    if (memoService_.isMemoValid()) {
        Logger::info(String("MemoService memo: ") + memoService_.getMemo());
    }

    if (aiService_.begin()) {
        Logger::info("AIService test passed");
    }

    if (webServerService_.begin()) {
        Logger::info("WebServerService test passed");
    }

    if (otaService_.begin()) {
        Logger::info("OTAService test passed");
    }
}

void AppController::update() {
    displayManager_.update();
    powerManager_.update();
    touchManager_.update();
    lvglPort_.update();
    uiManager_.update();
    timeService_.update();
    wifiService_.update();
    batteryService_.update();
    weatherService_.update();
    sdCardService_.update();
    albumService_.update();
    memoService_.update();
    aiService_.update();
    webServerService_.update();
    otaService_.update();

    static unsigned long lastPrint = 0;
    if (millis() - lastPrint >= 2000) {
        lastPrint = millis();
        Logger::info("running...");
        String wifiText = wifiService_.isConnected()
            ? String("WiFi: ") + wifiService_.getSSID()
            : "WiFi: Disconnected";
        uiManager_.setHomeWifiText(wifiText.c_str());
    }
}
