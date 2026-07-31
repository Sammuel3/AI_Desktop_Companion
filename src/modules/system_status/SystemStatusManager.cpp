#include "SystemStatusManager.h"
#include "../logger/Logger.h"

void SystemStatusManager::begin() {
    status_ = SystemStatus();
    Logger::info("SystemStatusManager initialized");
}

void SystemStatusManager::setWifiStatus(bool connected) {
    status_.wifiConnected = connected;
}

void SystemStatusManager::setBatteryLevel(int level) {
    status_.batteryLevel = level;
}

void SystemStatusManager::setWeather(const String& weather, float temperature) {
    status_.weather = weather;
    status_.temperature = temperature;
}

void SystemStatusManager::setTime(const String& time) {
    status_.currentTime = time;
}

void SystemStatusManager::setWebServerStatus(bool running) {
    status_.webServerRunning = running;
}

SystemStatus SystemStatusManager::getStatus() const {
    return status_;
}
