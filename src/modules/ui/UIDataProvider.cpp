#include "UIDataProvider.h"
#include "../logger/Logger.h"

UIDataProvider::UIDataProvider() {
}

bool UIDataProvider::begin(SystemStatusManager* status) {
    if (status == nullptr) {
        Logger::error("UIDataProvider: SystemStatusManager is null");
        return false;
    }
    status_ = status;
    cachedStatus_ = status_->getStatus();
    initialized_ = true;
    Logger::info("UIDataProvider initialized");
    return true;
}

void UIDataProvider::update() {
    if (status_ != nullptr) {
        cachedStatus_ = status_->getStatus();
    }
}

// ---- 直接数据转发 ----

String UIDataProvider::getTime() const {
    if (status_ == nullptr) return "--:--";
    return status_->getTime();
}

String UIDataProvider::getWeather() const {
    if (status_ == nullptr) return "Unknown";
    return status_->getWeather();
}

float UIDataProvider::getTemperature() const {
    if (status_ == nullptr) return 0.0f;
    return status_->getTemperature();
}

int UIDataProvider::getBatteryLevel() const {
    if (status_ == nullptr) return 100;
    return status_->getBatteryLevel();
}

bool UIDataProvider::isCharging() const {
    if (status_ == nullptr) return false;
    return status_->isCharging();
}

bool UIDataProvider::isWifiConnected() const {
    if (status_ == nullptr) return false;
    return status_->isWifiConnected();
}

String UIDataProvider::getDeviceName() const {
    return "SmartDesktop";
}

// ---- 格式化文本 ----

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

bool UIDataProvider::isInitialized() const {
    return initialized_;
}
