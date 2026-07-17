#include "OTAService.h"
#include "modules/logger/Logger.h"

bool OTAService::begin() {
    initialized_ = true;
    enabled_ = false;
    updating_ = false;
    progress_ = 0;
    statusText_ = "OTA: Disabled";
    Logger::info("OTAService initialized");
    return true;
}

void OTAService::update() {
    // 当前保持空实现，不输出周期日志，避免刷屏。
}

bool OTAService::isInitialized() const {
    return initialized_;
}

bool OTAService::isEnabled() const {
    return enabled_;
}

bool OTAService::isUpdating() const {
    return updating_;
}

uint8_t OTAService::getProgress() const {
    return progress_;
}

String OTAService::getStatusText() const {
    return statusText_;
}

void OTAService::setEnabled(bool enabled) {
    enabled_ = enabled;
    if (enabled_) {
        statusText_ = "OTA: Enabled";
    } else {
        statusText_ = "OTA: Disabled";
    }
    Logger::info(String("OTAService enabled: ") + (enabled_ ? "true" : "false"));
}
