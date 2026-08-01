#include "SystemStatusManager.h"
#include "../logger/Logger.h"

SystemStatusManager::SystemStatusManager() {
}

void SystemStatusManager::begin() {
    status_ = SystemStatus();
    initialized_ = true;
    Logger::info("SystemStatusManager initialized");
}

void SystemStatusManager::update() {
}

void SystemStatusManager::setWifiStatus(bool connected) {
    status_.wifiConnected = connected;
}

void SystemStatusManager::setBatteryLevel(int level) {
    status_.batteryLevel = level;
}

void SystemStatusManager::setCharging(bool charging) {
    status_.charging = charging;
}

void SystemStatusManager::setTime(const String& time) {
    status_.currentTime = time;
}

void SystemStatusManager::setWeather(const String& weather, float temperature) {
    status_.weather = weather;
    status_.temperature = temperature;
}

void SystemStatusManager::setWebServerStatus(bool running) {
    status_.webServerRunning = running;
}

bool SystemStatusManager::isWifiConnected() const {
    return status_.wifiConnected;
}

int SystemStatusManager::getBatteryLevel() const {
    return status_.batteryLevel;
}

bool SystemStatusManager::isCharging() const {
    return status_.charging;
}

String SystemStatusManager::getTime() const {
    return status_.currentTime;
}

String SystemStatusManager::getWeather() const {
    return status_.weather;
}

float SystemStatusManager::getTemperature() const {
    return status_.temperature;
}

SystemStatus SystemStatusManager::getStatus() const {
    return status_;
}

bool SystemStatusManager::isInitialized() const {
    return initialized_;
}
