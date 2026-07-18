#include "BatteryService.h"

bool BatteryService::begin() {
    initialized_ = true;
    return true;
}

void BatteryService::update() {
}

bool BatteryService::isInitialized() const {
    return initialized_;
}

bool BatteryService::isBatteryValid() const {
    return batteryValid_;
}

uint8_t BatteryService::getPercentage() const {
    if (!batteryValid_) {
        return 0;
    }
    return percentage_;
}

float BatteryService::getVoltage() const {
    if (!batteryValid_) {
        return 0.0f;
    }
    return voltage_;
}

bool BatteryService::isCharging() const {
    return charging_;
}
