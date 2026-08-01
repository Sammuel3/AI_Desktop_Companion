#include "PowerManager.h"
#include "../logger/Logger.h"

bool PowerManager::begin() {
    initialized_ = true;
    state_ = PowerState::ACTIVE;
    brightness_ = 80;
    Logger::info("PowerManager initialized");
    return true;
}

void PowerManager::update() {
}

void PowerManager::setBrightness(int level) {
    if (level < 0) level = 0;
    if (level > 100) level = 100;
    brightness_ = level;
}

int PowerManager::getBrightness() const {
    return brightness_;
}

void PowerManager::enterSleep() {
    state_ = PowerState::SLEEPING;
    Logger::info("Entering sleep mode");
}

void PowerManager::wakeUp() {
    state_ = PowerState::ACTIVE;
    Logger::info("Waking up");
}

bool PowerManager::isSleeping() const {
    return state_ == PowerState::SLEEPING;
}

bool PowerManager::isInitialized() const {
    return initialized_;
}
