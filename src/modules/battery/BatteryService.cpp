#include "BatteryService.h"
#include "../logger/Logger.h"

bool BatteryService::begin() {
    initialized_ = true;
    percentage_ = 100;
    charging_ = false;
    Logger::info("BatteryService initialized");
    return true;
}

void BatteryService::update() {
}

int BatteryService::getPercentage() const {
    return percentage_;
}

bool BatteryService::isCharging() const {
    return charging_;
}

bool BatteryService::isInitialized() const {
    return initialized_;
}
