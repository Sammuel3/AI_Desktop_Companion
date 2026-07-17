#include "PowerManager.h"
#include "modules/logger/Logger.h"

bool PowerManager::begin() {
    initialized_ = true;
    screenOn_ = true;
    sleepRequested_ = false;
    lastUserActivityMs_ = millis();
    statusText_ = "Power: Awake";
    Logger::info("PowerManager initialized");
    return true;
}

void PowerManager::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool PowerManager::isInitialized() const {
    return initialized_;
}

bool PowerManager::isScreenOn() const {
    return screenOn_;
}

bool PowerManager::isSleepRequested() const {
    return sleepRequested_;
}

String PowerManager::getStatusText() const {
    return statusText_;
}

void PowerManager::notifyUserActivity() {
    lastUserActivityMs_ = millis();
    sleepRequested_ = false;
    if (screenOn_) {
        statusText_ = "Power: Awake";
    }
    Logger::info("PowerManager user activity");
}

void PowerManager::requestSleep() {
    sleepRequested_ = true;
    statusText_ = "Power: Sleep requested";
    Logger::info("PowerManager sleep requested");
}

void PowerManager::cancelSleepRequest() {
    sleepRequested_ = false;
    statusText_ = screenOn_ ? "Power: Awake" : "Power: Screen off";
    Logger::info("PowerManager sleep request canceled");
}

void PowerManager::setScreenOn(bool on) {
    screenOn_ = on;
    statusText_ = screenOn_ ? "Power: Awake" : "Power: Screen off";
    Logger::info(String("PowerManager screen: ") + (screenOn_ ? "on" : "off"));
}
