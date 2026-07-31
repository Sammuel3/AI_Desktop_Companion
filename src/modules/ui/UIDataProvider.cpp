#include "UIDataProvider.h"
#include "../logger/Logger.h"

bool UIDataProvider::begin(SystemStatusManager* statusManager) {
    if (statusManager == nullptr) {
        Logger::error("UIDataProvider: SystemStatusManager is null");
        return false;
    }
    statusManager_ = statusManager;
    cachedStatus_ = statusManager_->getStatus();
    Logger::info("UIDataProvider initialized");
    return true;
}

void UIDataProvider::update() {
    if (statusManager_ != nullptr) {
        cachedStatus_ = statusManager_->getStatus();
    }
}

String UIDataProvider::getBatteryText() {
    return String(cachedStatus_.batteryLevel) + "%";
}

String UIDataProvider::getWeatherText() {
    return cachedStatus_.weather;
}

String UIDataProvider::getTemperatureText() {
    return String(cachedStatus_.temperature, 1) + "°C";
}

String UIDataProvider::getTimeText() {
    return cachedStatus_.currentTime;
}

String UIDataProvider::getWifiText() {
    if (cachedStatus_.wifiConnected) {
        return "WiFi: Connected";
    }
    return "WiFi: Disconnected";
}
