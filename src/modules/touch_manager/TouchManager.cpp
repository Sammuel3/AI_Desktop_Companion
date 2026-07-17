#include "TouchManager.h"
#include "modules/logger/Logger.h"

bool TouchManager::begin() {
    if (!touchDriver_.begin()) {
        Logger::error("GT911TouchDriver initialization failed");
        initialized_ = false;
        touched_ = false;
        x_ = 0;
        y_ = 0;
        return false;
    }
    initialized_ = true;
    touched_ = false;
    x_ = 0;
    y_ = 0;
    Logger::info("TouchManager initialized");
    return true;
}

void TouchManager::update() {
    if (!initialized_) {
        return;
    }
    touchDriver_.update();
    touched_ = touchDriver_.isTouched();
    if (touched_) {
        x_ = touchDriver_.getX();
        y_ = touchDriver_.getY();
    }
}

bool TouchManager::isTouched() const {
    return touched_;
}

uint16_t TouchManager::getX() const {
    return x_;
}

uint16_t TouchManager::getY() const {
    return y_;
}

bool TouchManager::isInitialized() const {
    return initialized_;
}
