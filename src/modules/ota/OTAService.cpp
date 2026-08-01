#include "OTAService.h"
#include "../logger/Logger.h"

OTAService::OTAService() {
}

bool OTAService::begin() {
    initialized_ = true;
    updating_ = false;
    progress_ = 0;
    Logger::info("OTAService initialized");
    return true;
}

void OTAService::update() {
}

bool OTAService::startUpdate() {
    if (!initialized_) {
        return false;
    }
    updating_ = true;
    progress_ = 0;
    Logger::info("OTA update started");
    return true;
}

void OTAService::stopUpdate() {
    updating_ = false;
    Logger::info("OTA update stopped");
}

bool OTAService::isUpdating() const {
    return updating_;
}

int OTAService::getProgress() const {
    return progress_;
}

bool OTAService::isInitialized() const {
    return initialized_;
}
