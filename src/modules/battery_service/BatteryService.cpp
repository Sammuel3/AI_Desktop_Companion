#include "BatteryService.h"
#include "modules/logger/Logger.h"

bool BatteryService::begin() {
    initialized_ = true;
    charging_ = false;
    batteryPercent_ = 0;
    batteryVoltage_ = 0.0f;
    statusText_ = "Battery: --%";
    Logger::info("BatteryService initialized");
    return true;
}

void BatteryService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool BatteryService::isInitialized() const {
    return initialized_;
}

bool BatteryService::isCharging() const {
    return charging_;
}

uint8_t BatteryService::getBatteryPercent() const {
    return batteryPercent_;
}

float BatteryService::getBatteryVoltage() const {
    return batteryVoltage_;
}

String BatteryService::getStatusText() const {
    return statusText_;
}
